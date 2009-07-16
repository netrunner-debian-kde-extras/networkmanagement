/*
Copyright 2009 Will Stephenson <wstephenson@kde.org>

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

#include "vpninterfaceconnectionprovider.h"

#include <QHash>
#include <QPointer>

#include <connection.h>
#include <vpninterfaceconnection.h>

#include "connectionlist.h"
#include "activatablelist.h"

class VpnInterfaceConnectionProviderPrivate
{
public:
    ConnectionList * connectionList;
    QPointer<ActivatableList> activatableList;
    QHash<QString, Knm::VpnInterfaceConnection*> vpns;
};

VpnInterfaceConnectionProvider::VpnInterfaceConnectionProvider(ConnectionList * connectionList, ActivatableList * activatableList, QObject * parent)
: QObject(parent), d_ptr(new VpnInterfaceConnectionProviderPrivate)
{
    Q_D(VpnInterfaceConnectionProvider);
    d->connectionList = connectionList;
    d->activatableList = activatableList;
}

VpnInterfaceConnectionProvider::~VpnInterfaceConnectionProvider()
{
    delete d_ptr;
}

void VpnInterfaceConnectionProvider::init()
{
    Q_D(VpnInterfaceConnectionProvider);
    // assess all connections
    foreach (QString uuid, d->connectionList->connections()) {
        Knm::Connection * connection = d->connectionList->findConnection(uuid);
        handleAdd(connection);
    }
}

void VpnInterfaceConnectionProvider::handleAdd(Knm::Connection * addedConnection)
{
    Q_D(VpnInterfaceConnectionProvider);
    if (!d->vpns.contains(addedConnection->uuid())) {
        if (addedConnection->type() == Knm::Connection::Vpn) {
            Knm::VpnInterfaceConnection * vpnConnection = new Knm::VpnInterfaceConnection(addedConnection->uuid(), addedConnection->name(), QLatin1String("any"), this);
            d->vpns.insert(addedConnection->uuid(), vpnConnection);
            d->activatableList->addActivatable(vpnConnection);
        }
    }
}

void VpnInterfaceConnectionProvider::handleUpdate(Knm::Connection * updatedConnection)
{
    Q_D(VpnInterfaceConnectionProvider);
    if (d->vpns.contains(updatedConnection->uuid())) {
        Knm::VpnInterfaceConnection * ifaceConnection = dynamic_cast<Knm::VpnInterfaceConnection *>(d->vpns[updatedConnection->uuid()]);
        // assume only the name changed here
        ifaceConnection->setConnectionName(updatedConnection->name());
    }
}

void VpnInterfaceConnectionProvider::handleRemove(Knm::Connection * removedConnection)
{
    Q_D(VpnInterfaceConnectionProvider);
    if (d->vpns.contains(removedConnection->uuid())) {
        Knm::VpnInterfaceConnection * activatable = d->vpns.take(removedConnection->uuid());
        d->activatableList->removeActivatable(activatable);
        delete activatable;
    }
}

// vim: sw=4 sts=4 et tw=100
