/*
Copyright 2008 Will Stephenson <wstephenson@kde.org>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) version 3, or any
later version accepted by the membership of KDE e.V. (or its
successor approved by the membership of KDE e.V.), which shall
act as a proxy defined in Section 6 of version 3 of the license.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VPNUIPLUGIN_H
#define VPNUIPLUGIN_H

#include <QObject>

#include "settingwidget.h"

#include "knm_export.h"

namespace Knm
{
    class Connection;
} // namespace Knm

class SettingWidget;

/**
 * Plugin for UI elements for VPN configuration
 */
class KNM_EXPORT VpnUiPlugin : public QObject
{
Q_OBJECT
public:
    VpnUiPlugin(QObject * parent = 0);
    virtual ~VpnUiPlugin();

    virtual SettingWidget * widget(Knm::Connection * connection, QWidget * parent = 0) = 0;
    virtual SettingWidget * askUser(Knm::Connection * connection, QWidget * parent = 0){ return widget(connection, parent); };
private:
    class Private;
    Private * d;
};

#endif // VPNUIPLUGIN_H
