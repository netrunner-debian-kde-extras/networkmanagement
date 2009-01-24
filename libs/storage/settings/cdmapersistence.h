// This file is generated by kconfig_compiler from cdma.kcfg.
// All changes you do to this file will be lost.
#ifndef KNM_CDMAPERSISTENCE_H
#define KNM_CDMAPERSISTENCE_H

#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "settingpersistence.h"
#include "knm_export.h"
namespace Knm {

class CdmaSetting;

class KNM_EXPORT CdmaPersistence : public SettingPersistence
{
  public:
    CdmaPersistence( CdmaSetting * setting, KSharedConfig::Ptr config, ConnectionPersistence::SecretStorageMode mode = ConnectionPersistence::Secure);
    ~CdmaPersistence();
    void load();
    void save();
    QMap<QString,QString> secrets() const;
    void restoreSecrets(QMap<QString,QString>) const;
};
}

#endif

