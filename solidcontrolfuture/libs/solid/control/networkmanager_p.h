/*  This file is part of the KDE project
    Copyright (C) 2006 Will Stephenson <wstephenson@kde.org>
    Copyright (C) 2006-2007 Kevin Ottens <ervin@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

*/
#ifndef SOLID_NETWORKMANAGER_P_H
#define SOLID_NETWORKMANAGER_P_H

#include <QObject>
#include <QMap>
#include <QPair>

#include "managerbase_p.h"

#include "networkmanager.h"
#include "networkinterface.h"

namespace Solid
{
namespace Control
{
    namespace Ifaces
    {
        class NetworkInterfaceNm09;
    }

    class NetworkManagerNm09Private : public NetworkManagerNm09::Notifier, public ManagerBaseNm09Private
    {
        Q_OBJECT
    public:
        NetworkManagerNm09Private();
        ~NetworkManagerNm09Private();

        NetworkInterfaceNm09List networkInterfaces();
        NetworkInterfaceNm09 *findNetworkInterface(const QString &uni);

    private Q_SLOTS:
        void _k_networkInterfaceAdded(const QString &uni);
        void _k_networkInterfaceRemoved(const QString &uni);
        void _k_destroyed(QObject *object);

    private:
        NetworkInterfaceNm09List buildDeviceList(const QStringList &uniList);
        QPair<NetworkInterfaceNm09 *, QObject *> findRegisteredNetworkInterface(const QString &uni);

        QMap<QString, QPair<NetworkInterfaceNm09 *, QObject *> > m_networkInterfaceMap;
        NetworkInterfaceNm09 m_invalidDevice;
    };
}
}

#endif
