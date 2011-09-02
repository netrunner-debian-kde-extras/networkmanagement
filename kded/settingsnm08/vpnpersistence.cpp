// This file is generated by kconfig_compiler from vpn.kcfg.
// All changes you do to this file will be lost.

#include "vpnpersistence.h"

#include <KUser>

using namespace Knm;

VpnPersistence::VpnPersistence(VpnSetting * setting, KSharedConfig::Ptr config, SettingPersistence::SecretStorageMode mode) : SettingPersistence(setting, config, mode)
{
}

VpnPersistence::~VpnPersistence()
{
}

void VpnPersistence::load()
{
  VpnSetting * setting = static_cast<VpnSetting *>(m_setting);
  setting->setServiceType(m_config->readEntry("ServiceType", ""));
  setting->setData(stringMapFromStringList(m_config->readEntry("Data", QStringList())));
  setting->setUserName(m_config->readEntry("UserName", ""));
  // SECRET
  if (m_storageMode == SettingPersistence::PlainText) {
      // the map is flattened to a list of key,value,key,value
      setting->setVpnSecrets(stringMapFromStringList(m_config->readEntry("VpnSecrets", QStringList())));
    setting->setSecretsAvailable(true);
  }
  setting->setPluginName(m_config->readEntry("PluginName", ""));
}

QStringMap VpnPersistence::stringMapFromStringList(const QStringList & list)
{
    QStringMap map;
    if (list.count() % 2 == 0) {
        for ( int i = 0; i < list.count(); i += 2 ) {
            map.insert( list[i], list[i+1] );
        }
    }
    return map;
}
