// This file is generated by kconfig_compiler from gsm.kcfg.
// All changes you do to this file will be lost.

#include "gsm.h"

using namespace Knm;

GsmSetting::GsmSetting() : Setting(Setting::Gsm), mNetworktype(-1), mBand(-1)
{
}

GsmSetting::~GsmSetting()
{
}

QString GsmSetting::name() const
{
  return QLatin1String("gsm");
}
bool GsmSetting::hasSecrets() const
{
  return true;
}
