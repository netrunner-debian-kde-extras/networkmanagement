// This file is generated by kconfig_compiler from pppoe.kcfg.
// All changes you do to this file will be lost.

#include "pppoedbus.h"

#include "pppoe.h"

PppoeDbus::PppoeDbus(Knm::PppoeSetting * setting) : SettingDbus(setting)
{
}

PppoeDbus::~PppoeDbus()
{
}

void PppoeDbus::fromMap(const QVariantMap & map)
{
    Knm::PppoeSetting * setting = static_cast<Knm::PppoeSetting *>(m_setting);
    if (map.contains(QLatin1String(NM_SETTING_PPPOE_SERVICE))) {
        setting->setService(map.value(QLatin1String(NM_SETTING_PPPOE_SERVICE)).value<QString>());
    }
    if (map.contains(QLatin1String(NM_SETTING_PPPOE_USERNAME))) {
        setting->setUsername(map.value(QLatin1String(NM_SETTING_PPPOE_USERNAME)).value<QString>());
    }
    // SECRET
    if (map.contains(QLatin1String(NM_SETTING_PPPOE_PASSWORD))) {
        setting->setPassword(map.value(QLatin1String(NM_SETTING_PPPOE_PASSWORD)).value<QString>());
    }
    setting->setPasswordflags((Knm::Setting::secretsTypes)map.value(QLatin1String(NM_SETTING_PPPOE_PASSWORD_FLAGS)).value<int>());
}

QVariantMap PppoeDbus::toMap()
{
    QVariantMap map;
    Knm::PppoeSetting * setting = static_cast<Knm::PppoeSetting *>(m_setting);
    map.insert(QLatin1String(NM_SETTING_PPPOE_USERNAME), setting->username());

    if (!setting->service().isEmpty()) {
        map.insert(QLatin1String(NM_SETTING_PPPOE_SERVICE), setting->service());
    }

    map.unite(toSecretsMap());
    if (!setting->password().isEmpty()) {
        map.insert(QLatin1String(NM_SETTING_PPPOE_PASSWORD_FLAGS), (int)setting->passwordflags());
    }
    return map;
}

QVariantMap PppoeDbus::toSecretsMap()
{
    QVariantMap map;
    Knm::PppoeSetting * setting = static_cast<Knm::PppoeSetting *>(m_setting);
    if (!setting->password().isEmpty())
        map.insert(QLatin1String(NM_SETTING_PPPOE_PASSWORD), setting->password());
    return map;
}

