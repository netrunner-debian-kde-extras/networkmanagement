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

#include "connectionwidgetfactory.h"

#include <KDebug>

#include "connectionwidget.h"

class ConnectionWidgetFactory::Private
{
public:
};

ConnectionWidgetFactory::ConnectionWidgetFactory() : d(0)
{

}

ConnectionWidgetFactory::~ConnectionWidgetFactory()
{
    delete d;
}

ConnectionWidget * ConnectionWidgetFactory::widgetForConnection(const QString & type) const
{
    // instantiate a ConnectionWidget
    ConnectionWidget * wid = new ConnectionWidget(0);
// add connection widgets to its tabwidget
    if (type == QLatin1String("wired")) {

    } else if ( type == QLatin1String("wireless")) {

    } else if ( type == QLatin1String("cellular")) {

    } else if ( type == QLatin1String("vpn")) {

    } else if ( type == QLatin1String("dsl")) {

    } else {
        kDebug() << "Connection type '" << type << "' is unknown!";
    }
// register it?
// return it
    return wid;
}

// vim: sw=4 sts=4 et tw=100
