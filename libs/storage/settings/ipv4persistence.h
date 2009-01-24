// This file is generated by kconfig_compiler from ipv4.kcfg.
// All changes you do to this file will be lost.
#ifndef KNM_IPV4PERSISTENCE_H
#define KNM_IPV4PERSISTENCE_H

#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "settingpersistence.h"
#include "knm_export.h"
namespace Knm {

class Ipv4Setting;

class KNM_EXPORT Ipv4Persistence : public SettingPersistence
{
  public:
    Ipv4Persistence( Ipv4Setting * setting, KSharedConfig::Ptr config, ConnectionPersistence::SecretStorageMode mode = ConnectionPersistence::Secure);
    ~Ipv4Persistence();
    void load();
    void save();
    QMap<QString,QString> secrets() const;
    void restoreSecrets(QMap<QString,QString>) const;
};
}

#endif

