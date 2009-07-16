/*
Copyright 2008 Frederik Gladhorn <gladhorn@kde.org>

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

#ifndef KNM_EXTERNALS_NETWORKITEM_H
#define KNM_EXTERNALS_NETWORKITEM_H

#include "activatable.h"
#include "wirelessitem.h"

#include <QtCore/QString>
#include <QObject>

#include "knminternals_export.h"

namespace Knm {

class KNMINTERNALS_EXPORT WirelessNetworkItem : public Activatable, public WirelessItem
{
Q_OBJECT
Q_PROPERTY(QString ssid READ ssid)
Q_PROPERTY(int strength READ strength)
Q_PROPERTY(uint wpaFlags READ wpaFlags)
Q_PROPERTY(uint rsnFlags READ rsnFlags)
public:
    WirelessNetworkItem(const QString & ssid, int strength, Solid::Control::AccessPoint::Capabilities capabilities, Solid::Control::AccessPoint::WpaFlags wpaFlags, Solid::Control::AccessPoint::WpaFlags rsnFlags, const QString & deviceUni, QObject * parent);
    virtual ~WirelessNetworkItem();
signals:
    void strengthChanged(int);
public Q_SLOTS:
    void setStrength(int);
};
} // namespace

#endif
