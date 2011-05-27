// This file is generated by kconfig_compiler from 802-11-wireless-security.kcfg.
// All changes you do to this file will be lost.

#include "802-11-wireless-securitypersistence.h"

#include "802-11-wireless-security.h"

using namespace Knm;

WirelessSecurityPersistence::WirelessSecurityPersistence(WirelessSecuritySetting * setting, KSharedConfig::Ptr config, ConnectionPersistence::SecretStorageMode mode) : SettingPersistence(setting, config, mode)
{
}

WirelessSecurityPersistence::~WirelessSecurityPersistence()
{
}

void WirelessSecurityPersistence::load()
{
    WirelessSecuritySetting * setting = static_cast<WirelessSecuritySetting *>(m_setting);
    if (m_config->exists()) { // this persistence saves nothing if there is no security, so the 
      // group won't exist.  not indenting the code inside this test to keep the diff clean ;)
    setting->setEnabled(true);
    QString contents = m_config->readEntry("securityType", "None");
    if (contents == "None")
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::None);
    else     if (contents == "StaticWep")
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::StaticWep);
    else     if (contents == "Leap")
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::Leap);
    else     if (contents == "DynamicWep")
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::DynamicWep);
    else     if (contents == "WpaPsk")
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::WpaPsk);
    else     if (contents == "WpaEap")
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::WpaEap);
    else     if (contents == "Wpa2Psk")
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::Wpa2Psk);
    else     if (contents == "Wpa2Eap")
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::Wpa2Eap);

  {
    QString contents = m_config->readEntry("keymgmt", "None");
    if (contents == "None")
      setting->setKeymgmt(WirelessSecuritySetting::EnumKeymgmt::None);
    else     if (contents == "Ieee8021x")
      setting->setKeymgmt(WirelessSecuritySetting::EnumKeymgmt::Ieee8021x);
    else     if (contents == "WPANone")
      setting->setKeymgmt(WirelessSecuritySetting::EnumKeymgmt::WPANone);
    else     if (contents == "WPAPSK")
      setting->setKeymgmt(WirelessSecuritySetting::EnumKeymgmt::WPAPSK);
    else     if (contents == "WPAEAP")
      setting->setKeymgmt(WirelessSecuritySetting::EnumKeymgmt::WPAEAP);

  }
  setting->setWeptxkeyindex(m_config->readEntry("weptxkeyindex", 0));
  {
    QString contents = m_config->readEntry("authalg", "none");
    if (contents == "none")
      setting->setAuthalg(WirelessSecuritySetting::EnumAuthalg::none);
    else     if (contents == "open")
      setting->setAuthalg(WirelessSecuritySetting::EnumAuthalg::open);
    else     if (contents == "shared")
      setting->setAuthalg(WirelessSecuritySetting::EnumAuthalg::shared);
    else     if (contents == "leap")
      setting->setAuthalg(WirelessSecuritySetting::EnumAuthalg::leap);

  }
  setting->setProto(m_config->readEntry("proto", QStringList()));
  setting->setPairwise(m_config->readEntry("pairwise", QStringList()));
  setting->setGroup(m_config->readEntry("group", QStringList()));
  setting->setLeapusername(m_config->readEntry("leapusername", ""));

  QString wepKeyType = m_config->readEntry("wepkeytype", "key");
  if (wepKeyType == "passphrase") {
      setting->setWepKeyType(Knm::WirelessSecuritySetting::Passphrase);
  } else if (wepKeyType == "hex") {
      setting->setWepKeyType(Knm::WirelessSecuritySetting::Hex);
  }

  // SECRETS
  if (m_storageMode == ConnectionPersistence::PlainText) {
    setting->setWepkey0(m_config->readEntry("wepkey0", ""));
    setting->setWepkey1(m_config->readEntry("wepkey1", ""));
    setting->setWepkey2(m_config->readEntry("wepkey2", ""));
    setting->setWepkey3(m_config->readEntry("wepkey3", ""));
    setting->setPsk(m_config->readEntry("psk", ""));
    setting->setLeappassword(m_config->readEntry("leappassword", ""));
    setting->setWeppassphrase(m_config->readEntry("weppassphrase", ""));
    setting->setSecretsAvailable(true);
  }
  } else {
      setting->setSecurityType(WirelessSecuritySetting::EnumSecurityType::None);
  }
  setting->setInitialized();
}

void WirelessSecurityPersistence::save()
{
  WirelessSecuritySetting * setting = static_cast<WirelessSecuritySetting *>(m_setting);
  if (!setting->enabled()) {
      m_config->deleteGroup();
      return;
  }
  switch (setting->securityType()) {
    case WirelessSecuritySetting::EnumSecurityType::None:
      m_config->deleteGroup();
      return; // don't save anything if no encryption
      break;
    case WirelessSecuritySetting::EnumSecurityType::StaticWep:
      m_config->writeEntry("securityType", "StaticWep");
      break;
    case WirelessSecuritySetting::EnumSecurityType::Leap:
      m_config->writeEntry("securityType", "Leap");
      break;
    case WirelessSecuritySetting::EnumSecurityType::DynamicWep:
      m_config->writeEntry("securityType", "DynamicWep");
      break;
    case WirelessSecuritySetting::EnumSecurityType::WpaPsk:
      m_config->writeEntry("securityType", "WpaPsk");
      break;
    case WirelessSecuritySetting::EnumSecurityType::WpaEap:
      m_config->writeEntry("securityType", "WpaEap");
      break;
    case WirelessSecuritySetting::EnumSecurityType::Wpa2Psk:
      m_config->writeEntry("securityType", "Wpa2Psk");
      break;
    case WirelessSecuritySetting::EnumSecurityType::Wpa2Eap:
      m_config->writeEntry("securityType", "Wpa2Eap");
      break;
  }
  switch (setting->keymgmt()) {
    case WirelessSecuritySetting::EnumKeymgmt::None:
      m_config->writeEntry("keymgmt", "None");
      break;
    case WirelessSecuritySetting::EnumKeymgmt::Ieee8021x:
      m_config->writeEntry("keymgmt", "Ieee8021x");
      break;
    case WirelessSecuritySetting::EnumKeymgmt::WPANone:
      m_config->writeEntry("keymgmt", "WPANone");
      break;
    case WirelessSecuritySetting::EnumKeymgmt::WPAPSK:
      m_config->writeEntry("keymgmt", "WPAPSK");
      break;
    case WirelessSecuritySetting::EnumKeymgmt::WPAEAP:
      m_config->writeEntry("keymgmt", "WPAEAP");
      break;
  }
  m_config->writeEntry("weptxkeyindex", setting->weptxkeyindex());
  switch (setting->authalg()) {
    case WirelessSecuritySetting::EnumAuthalg::none:
      m_config->writeEntry("authalg", "none");
      break;
    case WirelessSecuritySetting::EnumAuthalg::open:
      m_config->writeEntry("authalg", "open");
      break;
    case WirelessSecuritySetting::EnumAuthalg::shared:
      m_config->writeEntry("authalg", "shared");
      break;
    case WirelessSecuritySetting::EnumAuthalg::leap:
      m_config->writeEntry("authalg", "leap");
      break;
  }
  m_config->writeEntry("proto", setting->proto());
  m_config->writeEntry("pairwise", setting->pairwise());
  m_config->writeEntry("group", setting->group());
  m_config->writeEntry("leapusername", setting->leapusername());
  // SECRET
  if (m_storageMode == ConnectionPersistence::PlainText) {
    m_config->writeEntry("wepkey0", setting->wepkey0());
    m_config->writeEntry("wepkey1", setting->wepkey1());
    m_config->writeEntry("wepkey2", setting->wepkey2());
    m_config->writeEntry("wepkey3", setting->wepkey3());
    m_config->writeEntry("psk", setting->psk());
    m_config->writeEntry("leappassword", setting->leappassword());
    m_config->writeEntry("weppassphrase", setting->weppassphrase());
  }

  switch(setting->wepKeyType()) {
      case Knm::WirelessSecuritySetting::Passphrase: m_config->writeEntry("wepkeytype", "passphrase");
        break;
      case Knm::WirelessSecuritySetting::Hex: m_config->writeEntry("wepkeytype", "key");
        break;
      default:
        break;
  }
}

QMap<QString,QString> WirelessSecurityPersistence::secrets() const
{
  WirelessSecuritySetting * setting = static_cast<WirelessSecuritySetting *>(m_setting);
  QMap<QString,QString> map;
  if (setting->securityType() != WirelessSecuritySetting::EnumSecurityType::None) { // don't save anything if security is disabled
  map.insert(QLatin1String("wepkey0"), setting->wepkey0());
  map.insert(QLatin1String("wepkey1"), setting->wepkey1());
  map.insert(QLatin1String("wepkey2"), setting->wepkey2());
  map.insert(QLatin1String("wepkey3"), setting->wepkey3());
  map.insert(QLatin1String("psk"), setting->psk());
  map.insert(QLatin1String("leappassword"), setting->leappassword());
  map.insert(QLatin1String("weppassphrase"), setting->weppassphrase());
  }
  return map;
}

void WirelessSecurityPersistence::restoreSecrets(QMap<QString,QString> secrets) const
{
  if (m_storageMode == ConnectionPersistence::Secure) {
  WirelessSecuritySetting * setting = static_cast<WirelessSecuritySetting *>(m_setting);
    setting->setWepkey0(secrets.value("wepkey0"));
    setting->setWepkey1(secrets.value("wepkey1"));
    setting->setWepkey2(secrets.value("wepkey2"));
    setting->setWepkey3(secrets.value("wepkey3"));
    setting->setPsk(secrets.value("psk"));
    setting->setLeappassword(secrets.value("leappassword"));
    setting->setWeppassphrase(secrets.value("weppassphrase"));
    setting->setSecretsAvailable(true);
  }
}
