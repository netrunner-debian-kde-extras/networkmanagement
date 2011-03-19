/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -a exportedconnection -N -i marshalarguments.h -i types.h -i busconnection.h -l BusConnection -c ConnectionAdaptor introspection/nm-exported-connection.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "exportedconnection.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class ConnectionAdaptor
 */

ConnectionAdaptor::ConnectionAdaptor(BusConnection *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

ConnectionAdaptor::~ConnectionAdaptor()
{
    // destructor
}

void ConnectionAdaptor::Delete()
{
    // handle method call org.freedesktop.NetworkManagerSettings.Connection.Delete
    parent()->Delete();
}

QVariantMapMap ConnectionAdaptor::GetSettings()
{
    // handle method call org.freedesktop.NetworkManagerSettings.Connection.GetSettings
    return parent()->GetSettings();
}

void ConnectionAdaptor::Update(const QVariantMapMap &properties)
{
    // handle method call org.freedesktop.NetworkManagerSettings.Connection.Update
    parent()->Update(properties);
}

