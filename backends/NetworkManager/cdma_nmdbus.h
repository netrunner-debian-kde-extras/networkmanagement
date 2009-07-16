// This file is generated by kconfig_compiler from cdma.kcfg.
// All changes you do to this file will be lost.
#ifndef CDMADBUS_H
#define CDMADBUS_H

#include <nm-setting-cdma.h>

#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "settingdbus.h"
#include "knm_export.h"
class CdmaSetting;

class KNM_EXPORT CdmaDbus : public SettingNmDbus
{
  public:
    CdmaDbus( CdmaSetting * setting);
    ~CdmaDbus();
    void fromMap(const QVariantMap&);
    QVariantMap toMap();
    QVariantMap toSecretsMap();
};
#endif
