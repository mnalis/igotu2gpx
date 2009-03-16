/******************************************************************************
 * Copyright (C) 2009  Michael Hofmann <mh21@piware.de>                       *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License along    *
 * with this program; if not, write to the Free Software Foundation, Inc.,    *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.                *
 ******************************************************************************/

#include "igotu/commands.h"
#include "igotu/exception.h"
#include "igotu/libusbconnection.h"

#include <boost/scoped_ptr.hpp>

#include <QFile>

using namespace igotu;

int main()
{
    boost::scoped_ptr<DataConnection> connection;
    try {
        connection.reset(new LibusbConnection);
    } catch (const std::exception &e) {
        printf("Exception: %s\n", e.what());
        return 1;
    }

    // Just some dummy NMEA read, seems to help?
    try {
        for (unsigned i = 0; i < 10; ++i)
            connection->receive(16).data();
    } catch (const std::exception &e) {
        // ignored
    }

    try {
        NmeaSwitchCommand(connection.get(), false).sendAndReceive(true);

        IdentificationCommand id(connection.get());
        id.sendAndReceive();
        printf("S/N: %u\n", id.serialNumber());

        QFile file(QLatin1String("igotu.dump"));
        if (!file.open(QIODevice::WriteOnly))
            throw IgotuError(QCoreApplication::tr("Unable to write to file"));

        for (unsigned i = 0;; ++i) {
            printf("Dumping datablock %u...\n", i + 1);
            QByteArray data = ReadCommand(connection.get(), i * 0x1000, 0x1000)
                .sendAndReceive();
            if (data == QByteArray(0x1000, 0xff))
                break;
            file.write(data);
        }

        NmeaSwitchCommand(connection.get(), true).sendAndReceive();
    } catch (const std::exception &e) {
        printf("Exception: %s\n", e.what());
    }

    return 0;
}
