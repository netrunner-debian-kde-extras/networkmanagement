// This file is generated by kconfig_compiler from serial.kcfg.
// All changes you do to this file will be lost.

#include "serial.h"

using namespace Knm;

SerialSetting::SerialSetting() : Setting(Setting::Serial)
{
}

SerialSetting::~SerialSetting()
{
}

QString SerialSetting::name() const
{
  return QLatin1String("serial");
}
bool SerialSetting::hasSecrets() const
{
  return false;
}