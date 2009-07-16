// This file is generated by kconfig_compiler from pppoe.kcfg.
// All changes you do to this file will be lost.
#ifndef PPPOEDBUS_H
#define PPPOEDBUS_H

#include <nm-setting-pppoe.h>

#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "settingdbus.h"
#include "knm_export.h"
class PppoeSetting;

class KNM_EXPORT PppoeDbus : public SettingNmDbus
{
  public:
    PppoeDbus( PppoeSetting * setting);
    ~PppoeDbus();
    void fromMap(const QVariantMap&);
    QVariantMap toMap();
    QVariantMap toSecretsMap();
};
#endif

