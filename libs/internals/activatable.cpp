/*
Copyright 2008 Frederik Gladhorn <gladhorn@kde.org>
Copyright 2009 Will Stephenson <wstephenson@kde.org>

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

#include "activatable.h"

#include <QString>

#include <KDebug>

using namespace Knm;

Activatable::Activatable(ActivatableType type, const QString & deviceUni, QObject * parent)
: QObject(parent), m_type(type), m_deviceUni(deviceUni)
{
}

Activatable::~Activatable()
{
}

Activatable::ActivatableType Activatable::activatableType() const
{
    return m_type;
}

void Activatable::setDeviceUni(const QString& deviceUni)
{
    m_deviceUni = deviceUni;
}

QString Activatable::deviceUni() const
{
    return m_deviceUni;
}

void Activatable::activate()
{
    kDebug();
    emit activated();
}
