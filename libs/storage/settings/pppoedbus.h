// This file is generated by kconfig_compiler from pppoe.kcfg.
// All changes you do to this file will be lost.
#ifndef KNM_PPPOEDBUS_H
#define KNM_PPPOEDBUS_H

#include <nm-setting-pppoe.h>

#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "settingdbus.h"
#include "knm_export.h"
namespace Knm {

class PppoeSetting;

class KNM_EXPORT PppoeDbus : public SettingDbus
{
  public:
    PppoeDbus( PppoeSetting * setting);
    ~PppoeDbus();
    void fromMap(const QVariantMap&);
    QVariantMap toMap();
    QVariantMap toSecretsMap();
};
}

#endif

