/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -m -p nm-vpn-connectioninterface /space/kde/sources/trunk/playground/base/plasma/applets/networkmanager/backends/NetworkManager/introspection/nm-vpn-connection.xml
 *
 * qdbusxml2cpp is Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NM_VPN_CONNECTIONINTERFACE_H
#define NM_VPN_CONNECTIONINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.freedesktop.NetworkManager.VPN.Connection
 */
class OrgFreedesktopNetworkManagerVPNConnectionInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.NetworkManager.VPN.Connection"; }

public:
    OrgFreedesktopNetworkManagerVPNConnectionInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopNetworkManagerVPNConnectionInterface();

    Q_PROPERTY(QString Banner READ banner)
    inline QString banner() const
    { return qvariant_cast< QString >(internalPropGet("Banner")); }

    Q_PROPERTY(uint VpnState READ vpnState)
    inline uint vpnState() const
    { return qvariant_cast< uint >(internalPropGet("VpnState")); }

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void PropertiesChanged(const QVariantMap &properties);
    void VpnStateChanged(uint state, uint reason);
};

namespace org {
  namespace freedesktop {
    namespace NetworkManager {
      namespace VPN {
        typedef ::OrgFreedesktopNetworkManagerVPNConnectionInterface Connection;
      }
    }
  }
}
#endif
