// This file is generated by kconfig_compiler from vpn.kcfg.
// All changes you do to this file will be lost.
#ifndef KNM_VPNSETTING_H
#define KNM_VPNSETTING_H

#include <kglobal.h>
#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "setting.h"
#include "knminternals_export.h"
#include "../types.h"

namespace Knm {

class KNMINTERNALS_EXPORT VpnSetting : public Setting
{
  public:

    VpnSetting( );
    VpnSetting(VpnSetting *);
    ~VpnSetting();

    QString name() const;

    QMap<QString,QString> secretsToMap() const;
    void secretsFromMap(QMap<QString,QString>);
    static QStringList variantMapToStringList(const QVariantMap &);
    static QVariantMap variantMapFromStringList(const QStringList & list);
    static QStringMap stringMapFromStringList(const QStringList & list);
    static QStringList stringMapToStringList(const QStringMap & map);
    QStringList needSecrets(const bool requestNew = false) const;
    bool hasPersistentSecrets() const;

    /**
      Set Service Type
    */
    void setServiceType( const QString & v )
    {
        mServiceType = v;
    }

    /**
      Get Service Type
    */
    QString serviceType() const
    {
      return mServiceType;
    }

    /**
      Set Data bits
    */
    void setData( const QStringMap & v )
    {
        mData = v;
    }

    /**
      Get Data bits
    */
    QStringMap data() const
    {
      return mData;
    }

    /**
      Set Username
    */
    void setUserName( const QString & v )
    {
        mUserName = v;
    }

    /**
      Get Username
    */
    QString userName() const
    {
      return mUserName;
    }

    /**
      Set Vpnsecrets
    */
    void setVpnSecrets( const QStringMap & v )
    {
        mVpnSecrets = v;
    }

    /**
      Get Vpnsecrets
    */
    QStringMap vpnSecrets() const
    {
      return mVpnSecrets;
    }

    /**
      Set VPN Plugin Name
    */
    void setPluginName( const QString & v )
    {
        mPluginName = v;
    }

    /**
      Get VPN Plugin Name
    */
    QString pluginName() const
    {
      return mPluginName;
    }

  protected:
    static QVariantMap secretsToSave(const QStringMap &, const QStringMap &);
    // vpn
    QString mServiceType;
    QStringMap mData;
    QString mUserName;
    QStringMap mVpnSecrets;
    QString mPluginName;

  private:
};

}

#endif

