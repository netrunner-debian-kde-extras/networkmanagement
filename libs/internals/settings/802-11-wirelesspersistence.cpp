// This file is generated by kconfig_compiler from 802-11-wireless.kcfg.
// All changes you do to this file will be lost.

#include "802-11-wirelesspersistence.h"

#include "802-11-wireless.h"

using namespace Knm;

WirelessPersistence::WirelessPersistence(WirelessSetting * setting, KSharedConfig::Ptr config, ConnectionPersistence::SecretStorageMode mode) : SettingPersistence(setting, config, mode)
{
}

WirelessPersistence::~WirelessPersistence()
{
}

void WirelessPersistence::load()
{
  WirelessSetting * setting = static_cast<WirelessSetting *>(m_setting);
  setting->setSsid(m_config->readEntry("ssid", QByteArray()));
  {
    QString contents = m_config->readEntry("mode", "infrastructure");
    if (contents == "infrastructure")
      setting->setMode(WirelessSetting::EnumMode::infrastructure);
    else if (contents == "adhoc")
      setting->setMode(WirelessSetting::EnumMode::adhoc);

  }
  {
    QString contents = m_config->readEntry("band", "bg");
    if (contents == "a")
      setting->setBand(WirelessSetting::EnumBand::a);
    else if (contents == "bg")
      setting->setBand(WirelessSetting::EnumBand::bg);

  }
  setting->setChannel(m_config->readEntry("channel", 0));
  setting->setBssid(m_config->readEntry("bssid", QByteArray()));
  setting->setRate(m_config->readEntry("rate", 0));
  setting->setTxpower(m_config->readEntry("txpower", 0));
  setting->setMacaddressFromString(m_config->readEntry("macaddress", QString()));
  setting->setMtu(m_config->readEntry("mtu", 0));
  setting->setSeenbssids(m_config->readEntry("seenbssids", QStringList()));
  setting->setSecurity(m_config->readEntry("security", ""));
  setting->setInitialized();
}

void WirelessPersistence::save()
{
  WirelessSetting * setting = static_cast<WirelessSetting *>(m_setting);
  m_config->writeEntry("ssid", setting->ssid());
  switch (setting->mode()) {
    case WirelessSetting::EnumMode::infrastructure:
      m_config->writeEntry("mode", "infrastructure");
      break;
    case WirelessSetting::EnumMode::adhoc:
      m_config->writeEntry("mode", "adhoc");
      break;
  }
  switch (setting->band()) {
    case WirelessSetting::EnumBand::a:
      m_config->writeEntry("band", "a");
      break;
    case WirelessSetting::EnumBand::bg:
      m_config->writeEntry("band", "bg");
      break;
  }
  m_config->writeEntry("channel", setting->channel());
  m_config->writeEntry("bssid", setting->bssid());
  m_config->writeEntry("rate", setting->rate());
  m_config->writeEntry("txpower", setting->txpower());
  m_config->writeEntry("macaddress", setting->macaddressAsString());
  m_config->writeEntry("mtu", setting->mtu());
  if (setting->mode() != WirelessSetting::EnumMode::adhoc) {
      m_config->writeEntry("seenbssids", setting->seenbssids());
  }
kDebug() << setting->security();
  m_config->writeEntry("security", setting->security());
}

QMap<QString,QString> WirelessPersistence::secrets() const
{
  QMap<QString,QString> map;
  return map;
}

void WirelessPersistence::restoreSecrets(QMap<QString,QString> secrets) const
{
  if (m_storageMode == ConnectionPersistence::Secure) {
  Q_UNUSED(secrets);
  }
}
