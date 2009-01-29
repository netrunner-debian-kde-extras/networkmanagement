// This file is generated by kconfig_compiler from 802-11-wireless.kcfg.
// All changes you do to this file will be lost.
#ifndef KNM_WIRELESSDBUS_H
#define KNM_WIRELESSDBUS_H

#include <nm-setting-wireless.h>

#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "settingdbus.h"
#include "knm_export.h"
namespace Knm {

class WirelessSetting;

class KNM_EXPORT WirelessDbus : public SettingDbus
{
  public:
    WirelessDbus( WirelessSetting * setting);
    ~WirelessDbus();
    void fromMap(const QVariantMap&);
    QVariantMap toMap();
    QVariantMap toSecretsMap();
};
}

#endif
