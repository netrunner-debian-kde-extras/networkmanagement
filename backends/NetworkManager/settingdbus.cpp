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

#include "settingdbus.h"

using namespace Knm;

SettingDbus::SettingDbus(Setting * setting)
   : m_setting(setting)
{

}

SettingDbus::~SettingDbus()
{

}

void SettingDbus::insertIfTrue(QVariantMap& map, const char * key, bool setting)
{
    if (setting) {
        map.insert(QLatin1String(key), true);
    }
}

void SettingDbus::insertIfNonZero(QVariantMap& map, const char * key, uint setting)
{
    if (setting != 0) {
        map.insert(QLatin1String(key), setting);
    }
}

void SettingDbus::insertIfNonEmpty(QVariantMap& map, const char * key, const QString & setting)
{
    if (!setting.isEmpty()) {
        map.insert(QLatin1String(key), setting);
    }
}


// vim: sw=4 sts=4 et tw=100
