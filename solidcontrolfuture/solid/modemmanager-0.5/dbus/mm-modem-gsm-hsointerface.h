/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -N -m -p mm-modem-gsm-hsointerface introspection/mm-modem-gsm-hso.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef MM_MODEM_GSM_HSOINTERFACE_H
#define MM_MODEM_GSM_HSOINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.freedesktop.ModemManager.Modem.Gsm.Hso
 */
class OrgFreedesktopModemManagerModemGsmHsoInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.ModemManager.Modem.Gsm.Hso"; }

public:
    OrgFreedesktopModemManagerModemGsmHsoInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopModemManagerModemGsmHsoInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Authenticate(const QString &username, const QString &password)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(username) << qVariantFromValue(password);
        return asyncCallWithArgumentList(QLatin1String("Authenticate"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

#endif
