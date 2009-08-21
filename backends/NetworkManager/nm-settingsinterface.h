/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -N -i types.h -p nm-settingsinterface introspection/nm-settings.xml
 *
 * qdbusxml2cpp is Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NM_SETTINGSINTERFACE_H
#define NM_SETTINGSINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "types.h"

/*
 * Proxy class for interface org.freedesktop.NetworkManagerSettings
 */
class OrgFreedesktopNetworkManagerSettingsInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.NetworkManagerSettings"; }

public:
    OrgFreedesktopNetworkManagerSettingsInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopNetworkManagerSettingsInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QList<QDBusObjectPath> > ListConnections()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("ListConnections"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void NewConnection(const QDBusObjectPath &connection);
};

#endif
