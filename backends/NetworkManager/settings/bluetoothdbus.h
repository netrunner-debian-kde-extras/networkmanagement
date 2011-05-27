// This file is generated by kconfig_compiler from bluetooth.kcfg.
// All changes you do to this file will be lost.
#ifndef BLUETOOTHDBUS_H
#define BLUETOOTHDBUS_H

#include <nm-setting-bluetooth.h>

#include <kdebug.h>
#include <kcoreconfigskeleton.h>
#include "settingdbus.h"
#include "nm07dbus_export.h"
namespace Knm{
    class BluetoothSetting;
}

class NM07DBUS_EXPORT BluetoothDbus : public SettingDbus
{
  public:
    BluetoothDbus(Knm::BluetoothSetting * setting);
    ~BluetoothDbus();
    void fromMap(const QVariantMap&);
    QVariantMap toMap();
    QVariantMap toSecretsMap();
};
#endif

