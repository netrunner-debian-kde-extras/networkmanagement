/*
Copyright 2008 Will Stephenson <wstephenson@kde.org>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "wirelesssecuritysettingwidget.h"
#include "settingwidget_p.h"

#include <solid/control/networkmanager.h>
#include <solid/control/networkinterface.h>
#include <solid/control/wirelessnetworkinterface.h>
#include <solid/control/wirelessaccesspoint.h>

#include <KDebug>

#include <connection.h>
#include <settings/802-1x.h>
#include <settings/802-11-wireless.h>
#include <settings/802-11-wireless-security.h>

#include <wirelesssecurityidentifier.h>

#include "ui_wirelesssecurity.h"
#include "securitywidget.h"

#include "nullsecuritywidget.h"
#include "wepwidget.h"
#include "securityleap.h"
#include "securitydynamicwep.h"
#include "wpapskwidget.h"
#include "wpaeapwidget.h"

/**
 * Used to relate a security widget instance to its index in the QStackedWidget of security widgets
 */
class SecurityWidgetPair : public QPair<int, SecurityWidget*>
{
public:
    SecurityWidgetPair()
    {
        first = -1;
        second = 0;
    }
};

class WirelessSecuritySettingWidgetPrivate : public SettingWidgetPrivate
{
public:
    WirelessSecuritySettingWidgetPrivate()
        : settingWireless(0), settingSecurity(0), setting8021x(0)
    {
    }

    void registerSecurityType(SecurityWidgetPair & security, const QString & label)
    {
        ui.cboType->addItem(label);
        security.first = ui.securityWidgets->addWidget(security.second);
    }

    void setCurrentSecurityWidget(int index)
    {
        if (index >= 0 && index < ui.securityWidgets->count()) {
            ui.cboType->setCurrentIndex(index);
            ui.securityWidgets->setCurrentIndex(index);
        }
    }

    void clearSecurityWidgets()
    {
        nullSecurity.first = -1;
        staticWep.first = -1;
        leap.first = -1;
        dynamicWep.first = -1;
        wpaPsk.first = -1;
        wpaEap.first = -1;

        ui.cboType->clear();

        while (ui.securityWidgets->count()) {
            ui.securityWidgets->removeWidget(ui.securityWidgets->currentWidget());
        }
    }

    SecurityWidget * currentSecurityWidget() const
    {
        return static_cast<SecurityWidget*>(ui.securityWidgets->currentWidget());
    }

    Ui_WirelessSecurity ui;
    SecurityWidgetPair nullSecurity;
    SecurityWidgetPair staticWep;
    SecurityWidgetPair leap;
    SecurityWidgetPair dynamicWep;
    SecurityWidgetPair wpaPsk;
    SecurityWidgetPair wpaEap;

    Knm::WirelessSetting * settingWireless;
    Knm::WirelessSecuritySetting * settingSecurity;
    Knm::Security8021xSetting * setting8021x;
};

WirelessSecuritySettingWidget::WirelessSecuritySettingWidget(
        Knm::Connection * connection,
        Solid::Control::WirelessNetworkInterface * iface,
        Solid::Control::AccessPoint * ap,
        QWidget * parent)
: SettingWidget(*new WirelessSecuritySettingWidgetPrivate, connection, parent)
{
    Q_D(WirelessSecuritySettingWidget);

    d->ui.setupUi(this);
    QObject::connect(d->ui.cboType, SIGNAL(activated(int)), this, SLOT(securityTypeChanged(int)));

    d->settingWireless = static_cast<Knm::WirelessSetting *>(connection->setting(Knm::Setting::Wireless));
    d->settingSecurity = static_cast<Knm::WirelessSecuritySetting *>(connection->setting(Knm::Setting::WirelessSecurity));
    d->setting8021x = static_cast<Knm::Security8021xSetting *>(connection->setting(Knm::Setting::Security8021x));

    setIfaceAndAccessPoint(iface, ap);
}

void WirelessSecuritySettingWidget::setIfaceAndAccessPoint(Solid::Control::WirelessNetworkInterface * iface, Solid::Control::AccessPoint * ap)
{
    Q_D(WirelessSecuritySettingWidget);
    d->clearSecurityWidgets();

    // cache ap and device capabilities here
    Solid::Control::WirelessNetworkInterface::Capabilities ifaceCaps(0);
    bool adhoc = false;
    Solid::Control::AccessPoint::Capabilities apCaps(0);
    Solid::Control::AccessPoint::WpaFlags apWpa(0);
    Solid::Control::AccessPoint::WpaFlags apRsn(0);


    if (iface) {
        ifaceCaps = iface->wirelessCapabilities();
        if (ap) {
            apCaps = ap->capabilities();
            adhoc = (ap->mode() == Solid::Control::WirelessNetworkInterface::Adhoc);
            apWpa = ap->wpaFlags();
            apRsn = ap->rsnFlags();
        }
    } else {
        foreach (Solid::Control::NetworkInterface * candidate , Solid::Control::NetworkManager::networkInterfaces()) {
            if (candidate->type() == Solid::Control::NetworkInterface::Ieee80211) {
                Solid::Control::WirelessNetworkInterface * wirelessIface = qobject_cast<Solid::Control::WirelessNetworkInterface*>(candidate);
                if (wirelessIface) {
                    ifaceCaps |= wirelessIface->wirelessCapabilities();
                }
            }
        }
    }

    // populate cboType with appropriate wireless security types


    // insecure
    if (Knm::WirelessSecurity::possible(Knm::WirelessSecurity::None, ifaceCaps, (ap != 0), adhoc, apCaps, apWpa, apRsn)) {
        if (!d->nullSecurity.second) {
            d->nullSecurity.second = new NullSecurityWidget(d->connection, this);
        }
        d->registerSecurityType( d->nullSecurity, i18nc("Label for no wireless security", "None"));
    }

    // LEAP
    if (Knm::WirelessSecurity::possible(Knm::WirelessSecurity::Leap, ifaceCaps, (ap != 0), adhoc, apCaps, apWpa, apRsn)) {
        if (!d->leap.second) {
            d->leap.second = new LeapWidget(d->connection, this);
        }
        d->registerSecurityType(d->leap, i18nc("Label for LEAP wireless security", "LEAP"));
    }

    // Dynamic WEP
    if (Knm::WirelessSecurity::possible(Knm::WirelessSecurity::DynamicWep, ifaceCaps, (ap != 0), adhoc, apCaps, apWpa, apRsn)) {
        if (!d->dynamicWep.second) {
            d->dynamicWep.second = new SecurityDynamicWep(d->connection, this);
        }
        d->registerSecurityType(d->dynamicWep, i18nc("Label for Dynamic WEP wireless security", "Dynamic WEP (802.1x)"));
    }

    // WEP
    if (Knm::WirelessSecurity::possible(Knm::WirelessSecurity::StaticWep, ifaceCaps, (ap != 0), adhoc, apCaps, apWpa, apRsn)) {
        if (!d->staticWep.second) {
            d->staticWep.second = new WepWidget(WepWidget::Passphrase, d->connection, this);
        }
        d->registerSecurityType(d->staticWep, i18nc("Label for WEP wireless security", "WEP"));
    }

    // WPA-PSK
    if (Knm::WirelessSecurity::possible(Knm::WirelessSecurity::WpaPsk, ifaceCaps, (ap != 0), adhoc, apCaps, apWpa, apRsn)
            || Knm::WirelessSecurity::possible(Knm::WirelessSecurity::Wpa2Psk, ifaceCaps, (ap != 0), adhoc, apCaps, apWpa, apRsn)
       ) {
        if (!d->wpaPsk.second) {
            d->wpaPsk.second = new WpaPskWidget(d->connection, this);
        }
        d->registerSecurityType(d->wpaPsk, i18nc("Label for WPA-PSK wireless security", "WPA/WPA2 Personal"));
    }
    // WPA-EAP
    if (Knm::WirelessSecurity::possible(Knm::WirelessSecurity::WpaEap, ifaceCaps, (ap != 0), adhoc, apCaps, apWpa, apRsn)
            || Knm::WirelessSecurity::possible(Knm::WirelessSecurity::Wpa2Eap, ifaceCaps, (ap != 0), adhoc, apCaps, apWpa, apRsn)
                ) {
        if (!d->wpaEap.second) {
            d->wpaEap.second = new WpaEapWidget(d->connection, this);
        }
        d->registerSecurityType(d->wpaEap, i18nc("Label for WPA-EAP wireless security", "WPA/WPA2 Enterprise"));
    }
    d->setCurrentSecurityWidget(d->ui.cboType->count() - 1);
}

WirelessSecuritySettingWidget::~WirelessSecuritySettingWidget()
{
}

void WirelessSecuritySettingWidget::securityTypeChanged(int index)
{
    Q_D(WirelessSecuritySettingWidget);
    d->settingSecurity->reset();
    d->ui.securityWidgets->setCurrentIndex(index);
}

void WirelessSecuritySettingWidget::readConfig()
{
    Q_D(WirelessSecuritySettingWidget);
    SecurityWidget * sw = 0;
    if (d->settingWireless->security().isEmpty()) {
        d->setCurrentSecurityWidget(d->nullSecurity.first);
    } else {
        if (d->settingSecurity->isNull()) {
            //HACK - default new connections without an AP or those which support both EAP and PSK to WPA-PSK.
            if (d->wpaPsk.first >= 0) {
                d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::WpaPsk);
            } else if (d->wpaEap.first >= 0) {
                d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::WpaEap);
            } else if (d->staticWep.first >= 0) {
                d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::StaticWep);
            }
        }
        // this will break if the setting's configured security type is not supported by any of the
        // current hardware!
        switch (d->settingSecurity->securityType()) {
            case Knm::WirelessSecuritySetting::EnumSecurityType::None:
                d->setCurrentSecurityWidget(d->nullSecurity.first);
                break;
            case Knm::WirelessSecuritySetting::EnumSecurityType::StaticWep:
                d->setCurrentSecurityWidget(d->staticWep.first);
                break;
            case Knm::WirelessSecuritySetting::EnumSecurityType::Leap:
                d->setCurrentSecurityWidget(d->leap.first);
                break;
            case Knm::WirelessSecuritySetting::EnumSecurityType::DynamicWep:
                d->setCurrentSecurityWidget(d->dynamicWep.first);
                break;
            case Knm::WirelessSecuritySetting::EnumSecurityType::WpaPsk:
                d->setCurrentSecurityWidget(d->wpaPsk.first);
                break;
            case Knm::WirelessSecuritySetting::EnumSecurityType::WpaEap:
                d->setCurrentSecurityWidget(d->wpaEap.first);
                break;
        }

        sw = d->currentSecurityWidget();
        sw->readConfig();
    }
}

void WirelessSecuritySettingWidget::readSecrets()
{
    Q_D(WirelessSecuritySettingWidget);
    SecurityWidget * sw = d->currentSecurityWidget();
    sw->readSecrets();
}

void WirelessSecuritySettingWidget::writeConfig()
{
    Q_D(WirelessSecuritySettingWidget);
    d->settingWireless->setSecurity(d->settingSecurity->name());
    if (d->ui.cboType->currentIndex() == d->nullSecurity.first) {
        d->setting8021x->setEnabled(false);
        d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::None);
        d->settingWireless->setSecurity("");
    }
    else if (d->ui.cboType->currentIndex() == d->staticWep.first) {
        d->setting8021x->setEnabled(false);
        d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::StaticWep); // FIXME
        d->settingSecurity->setKeymgmt(Knm::WirelessSecuritySetting::EnumKeymgmt::None);
    }
    else if (d->ui.cboType->currentIndex() == d->leap.first) {
        d->setting8021x->setEnabled(false);
        d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::Leap); // FIXME
    }
    else if (d->ui.cboType->currentIndex() == d->dynamicWep.first) {
        d->setting8021x->setEnabled(true);
        d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::DynamicWep); // FIXME
        d->settingSecurity->setKeymgmt(Knm::WirelessSecuritySetting::EnumKeymgmt::WPAEAP);
    }
    else if (d->ui.cboType->currentIndex() == d->wpaPsk.first) {
        d->setting8021x->setEnabled(false);
        d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::WpaPsk); // FIXME
        d->settingSecurity->setKeymgmt(Knm::WirelessSecuritySetting::EnumKeymgmt::WPAPSK);
    }
    else if (d->ui.cboType->currentIndex() == d->wpaEap.first) {
        d->setting8021x->setEnabled(true);
        d->settingSecurity->setSecurityType(Knm::WirelessSecuritySetting::EnumSecurityType::WpaEap); // FIXME
        d->settingSecurity->setKeymgmt(Knm::WirelessSecuritySetting::EnumKeymgmt::WPAEAP);
    }

    SecurityWidget * sw = d->currentSecurityWidget();
    if (sw) {
        sw->writeConfig();
    }
    d->settingSecurity->setInitialized();
    d->setting8021x->setInitialized();
}

void WirelessSecuritySettingWidget::validate()
{

}

// vim: sw=4 sts=4 et tw=100