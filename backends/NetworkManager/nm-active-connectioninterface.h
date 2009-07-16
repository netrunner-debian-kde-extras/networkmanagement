/*
 * This file was generated by dbusxml2cpp version 0.6
 * Command line was: dbusxml2cpp -N -m -p nm-active-connectioninterface /space/kde/sources/trunk/playground/base/plasma/applets/networkmanager/settings/dbus/introspection/nm-active-connection.xml
 *
 * dbusxml2cpp is Copyright (C) 2006 Trolltech ASA. All rights reserved.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NM_ACTIVE_CONNECTIONINTERFACE_H_1224281770
#define NM_ACTIVE_CONNECTIONINTERFACE_H_1224281770

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#include "../types.h"
#include "../knm_export.h"

/*
 * Proxy class for interface org.freedesktop.NetworkManager.Connection.Active
 */
class KNM_EXPORT OrgFreedesktopNetworkManagerConnectionActiveInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.NetworkManager.Connection.Active"; }

public:
    OrgFreedesktopNetworkManagerConnectionActiveInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopNetworkManagerConnectionActiveInterface();

    Q_PROPERTY(QDBusObjectPath Connection READ connection)
    inline QDBusObjectPath connection() const
    { return qvariant_cast< QDBusObjectPath >(internalPropGet("Connection")); }

    Q_PROPERTY(bool Default READ getDefault)
    inline bool getDefault() const
    { return qvariant_cast< bool >(internalPropGet("Default")); }

    Q_PROPERTY(QList<QDBusObjectPath> Devices READ devices)
    inline QList<QDBusObjectPath> devices() const
    { return qvariant_cast< QList<QDBusObjectPath> >(internalPropGet("Devices")); }

    Q_PROPERTY(QString ServiceName READ serviceName)
    inline QString serviceName() const
    { return qvariant_cast< QString >(internalPropGet("ServiceName")); }

    Q_PROPERTY(QDBusObjectPath SpecificObject READ specificObject)
    inline QDBusObjectPath specificObject() const
    { return qvariant_cast< QDBusObjectPath >(internalPropGet("SpecificObject")); }

    Q_PROPERTY(uint State READ state)
    inline uint state() const
    { return qvariant_cast< uint >(internalPropGet("State")); }

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void PropertiesChanged(const QVariantMap &properties);
};

#endif