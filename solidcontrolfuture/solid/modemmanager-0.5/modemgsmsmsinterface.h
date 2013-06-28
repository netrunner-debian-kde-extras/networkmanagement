/*
Copyright 2008 Will Stephenson <wstephenson@kde.org>
Copyright 2010 Lamarque Souza <lamarque@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MM05_MODEMGSMSMSINTERFACE_H
#define MM05_MODEMGSMSMSINTERFACE_H

#include "modeminterface.h"
#include "solid/control/ifaces/modemgsmsmsinterface.h"
#include "dbus/generic-types.h"

class MMModemGsmSmsInterfacePrivate;

class KDE_EXPORT MMModemGsmSmsInterface : public MMModemInterface, virtual public Solid::Control::Ifaces::ModemGsmSmsInterface
{
Q_OBJECT
Q_DECLARE_PRIVATE(MMModemGsmSmsInterface)
Q_INTERFACES(Solid::Control::Ifaces::ModemGsmSmsInterface)

public:
    MMModemGsmSmsInterface(const QString & path, MMModemManager * manager, QObject * parent);
    ~MMModemGsmSmsInterface();

    void deleteSms(const int index);
    QVariantMap get(const int index);
    int getFormat();
    void setFormat(const int format);
    QString getSmsc();
    QList<QVariantMap> list();
    void save(const QVariantMap & properties);
    void send(const QVariantMap & properties);
    void sendFromStorage(const int index);
    void setIndication(const int mode, const int mt, const int bm, const int ds, const int brf);

Q_SIGNALS:
    void smsReceived(int index, bool complete);
    void completed(int index, bool completed);
};

#endif

