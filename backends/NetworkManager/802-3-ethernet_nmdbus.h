// This file is generated by kconfig_compiler from 802-3-ethernet.kcfg.
// All changes you do to this file will be lost.
#ifndef WIREDDBUS_H
#define WIREDDBUS_H

#include <nm-setting-wired.h>

#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "settingdbus.h"
#include "knm_export.h"
class WiredSetting;

class KNM_EXPORT WiredDbus : public SettingNmDbus
{
  public:
    WiredDbus( WiredSetting * setting);
    ~WiredDbus();
    void fromMap(const QVariantMap&);
    QVariantMap toMap();
    QVariantMap toSecretsMap();
};
#endif
