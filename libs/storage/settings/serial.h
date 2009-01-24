// This file is generated by kconfig_compiler from serial.kcfg.
// All changes you do to this file will be lost.
#ifndef KNM_SERIALSETTING_H
#define KNM_SERIALSETTING_H

#include <kglobal.h>
#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "setting.h"
#include "knm_export.h"
namespace Knm {

class KNM_EXPORT SerialSetting : public Setting
{
  public:
    class EnumParity
    {
      public:
      enum type { None, Even, Odd, COUNT };
    };

    SerialSetting( );
    ~SerialSetting();

    QString name() const;

    bool hasSecrets() const;

    /**
      Set Baud
    */
    void setBaud( uint v )
    {
        mBaud = v;
    }

    /**
      Get Baud
    */
    uint baud() const
    {
      return mBaud;
    }

    /**
      Set Data bits
    */
    void setBits( uint v )
    {
        mBits = v;
    }

    /**
      Get Data bits
    */
    uint bits() const
    {
      return mBits;
    }

    /**
      Set Parity
    */
    void setParity( const QString & v )
    {
        mParity = v;
    }

    /**
      Get Parity
    */
    QString parity() const
    {
      return mParity;
    }

    /**
      Set Stop bits
    */
    void setStopbits( uint v )
    {
        mStopbits = v;
    }

    /**
      Get Stop bits
    */
    uint stopbits() const
    {
      return mStopbits;
    }

    /**
      Set Send delay
    */
    void setSenddelay( quint64 v )
    {
        mSenddelay = v;
    }

    /**
      Get Send delay
    */
    quint64 senddelay() const
    {
      return mSenddelay;
    }

  protected:

    // serial
    uint mBaud;
    uint mBits;
    QString mParity;
    uint mStopbits;
    quint64 mSenddelay;

  private:
};

}

#endif

