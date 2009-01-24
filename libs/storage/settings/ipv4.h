// This file is generated by kconfig_compiler from ipv4.kcfg.
// All changes you do to this file will be lost.
#ifndef KNM_IPV4SETTING_H
#define KNM_IPV4SETTING_H

#include <kglobal.h>
#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "setting.h"
#include "knm_export.h"
namespace Knm {

class KNM_EXPORT Ipv4Setting : public Setting
{
  public:
    class EnumMethod
    {
      public:
      enum type { Automatic, LinkLocal, Manual, Shared, COUNT };
    };

    Ipv4Setting( );
    ~Ipv4Setting();

    QString name() const;

    bool hasSecrets() const;

    /**
      Set Method
    */
    void setMethod( int v )
    {
        mMethod = v;
    }

    /**
      Get Method
    */
    int method() const
    {
      return mMethod;
    }

    /**
      Set DNS Servers
    */
    void setDns( const QStringList & v )
    {
        mDns = v;
    }

    /**
      Get DNS Servers
    */
    QStringList dns() const
    {
      return mDns;
    }

    /**
      Set Search Domains
    */
    void setDnssearch( const QStringList & v )
    {
        mDnssearch = v;
    }

    /**
      Get Search Domains
    */
    QStringList dnssearch() const
    {
      return mDnssearch;
    }

    /**
      Set IP Addresses
    */
    void setAddresses( const QStringList & v )
    {
        mAddresses = v;
    }

    /**
      Get IP Addresses
    */
    QStringList addresses() const
    {
      return mAddresses;
    }

    /**
      Set Ignore DHCP DNS
    */
    void setIgnoredhcpdns( bool v )
    {
        mIgnoredhcpdns = v;
    }

    /**
      Get Ignore DHCP DNS
    */
    bool ignoredhcpdns() const
    {
      return mIgnoredhcpdns;
    }

  protected:

    // ipv4
    int mMethod;
    QStringList mDns;
    QStringList mDnssearch;
    QStringList mAddresses;
    bool mIgnoredhcpdns;

  private:
};

}

#endif

