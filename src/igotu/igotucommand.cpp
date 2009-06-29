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

#include "dataconnection.h"
#include "exception.h"
#include "igotucommand.h"
#include "verbose.h"

#include <QtEndian>

#include <numeric>

namespace igotu
{

class IgotuCommandPrivate
{
public:
    unsigned sendCommand(const QByteArray &data);
    int receiveResponseSize();
    QByteArray receiveResponseRemainder(unsigned size);

    DataConnection *connection;
    QByteArray command;
    bool receiveRemainder;
    bool ignoreProtocolErrors;
    bool purgeBuffersBeforeSend;
};

// IgotuCommandPrivate =========================================================

int IgotuCommandPrivate::receiveResponseSize()
{
    QByteArray data(connection->receive(3));
    if (data.size() != 3)
        throw IgotuProtocolError(IgotuCommand::tr
                ("Response too short: expected %1, got %2 bytes")
                .arg(3).arg(data.size()));
    if (data[0] != '\x93')
        throw IgotuProtocolError(IgotuCommand::tr("Invalid reply packet: %1")
                .arg(QString::fromAscii(data.toHex())));
    return qFromBigEndian<qint16>(reinterpret_cast<const uchar*>
            (data.data() + 1));
}

QByteArray IgotuCommandPrivate::receiveResponseRemainder(unsigned size)
{
    const QByteArray result = connection->receive(size);
    if (unsigned(result.size()) != size)
        throw IgotuProtocolError(IgotuCommand::tr
                ("Response remainder too short: expected %1, got %2 bytes")
                .arg(size).arg(result.size()));
    return result;
}

unsigned IgotuCommandPrivate::sendCommand(const QByteArray &data)
{
    QByteArray command(data);
    unsigned pieces = (command.size() + 7) / 8;
    command += QByteArray(pieces * 8 - command.size(), 0);

    if (command.isEmpty())
        return 0;

    command[command.size() - 1] = -std::accumulate(command.data() + 0,
            command.data() + command.size() - 2, 0);
    int responseSize = 0;
    for (unsigned i = 0; i < pieces; ++i) {
        // TODO: check whether it is ok to purge the buffers before *all*
        // commands on Mac OS X
        connection->send(command.mid(i * 8, 8), i == 0 &&
                purgeBuffersBeforeSend);
        responseSize = receiveResponseSize();
        if (responseSize < 0)
            throw IgotuDeviceError(IgotuCommand::tr("Device responded with error code: %1")
                 .arg(responseSize));
        if (responseSize != 0 && i + 1 < pieces)
            throw IgotuProtocolError(IgotuCommand::tr
                    ("Non-empty intermediate reply packet: %1")
                    .arg(QString::fromAscii(data.toHex())));
    }
    return responseSize;
}

// IgotuCommand ================================================================

IgotuCommand::IgotuCommand(DataConnection *connection, const QByteArray
        &command, bool receiveRemainder) :
    dataPtr(new IgotuCommandPrivate)
{
    D(IgotuCommand);

    d->connection = connection;
    d->command = command;
    d->receiveRemainder = receiveRemainder;
    d->ignoreProtocolErrors = false;
    d->purgeBuffersBeforeSend = false;
}

IgotuCommand::~IgotuCommand()
{
}

QByteArray IgotuCommand::command() const
{
    D(const IgotuCommand);

    return d->command;
}

void IgotuCommand::setCommand(const QByteArray &command)
{
    D(IgotuCommand);

    d->command = command;
}

DataConnection *IgotuCommand::connection() const
{
    D(const IgotuCommand);

    return d->connection;
}

void IgotuCommand::setConnection(DataConnection *connection)
{
    D(IgotuCommand);

    d->connection = connection;
}

bool IgotuCommand::receiveRemainder() const
{
    D(const IgotuCommand);

    return d->receiveRemainder;
}

void IgotuCommand::setReceiveRemainder(bool value)
{
    D(IgotuCommand);

    d->receiveRemainder = value;
}

bool IgotuCommand::ignoreProtocolErrors() const
{
    D(const IgotuCommand);

    return d->ignoreProtocolErrors;
}

void IgotuCommand::setIgnoreProtocolErrors(bool value)
{
    D(IgotuCommand);

    d->ignoreProtocolErrors = value;
}

bool IgotuCommand::purgeBuffersBeforeSend() const
{
    D(const IgotuCommand);

    return d->purgeBuffersBeforeSend;
}

void IgotuCommand::setPurgeBuffersBeforeSend(bool value)
{
    D(IgotuCommand);

    d->purgeBuffersBeforeSend = value;
}

QByteArray IgotuCommand::sendAndReceive()
{
    D(IgotuCommand);

    unsigned protocolErrors = 0;
    unsigned deviceErrors = 0;
    try {
        Q_FOREVER {
            unsigned size;
            QByteArray remainder;

            try {
                size = d->sendCommand(d->command);
                if (size > 0 && d->receiveRemainder)
                    remainder = d->receiveResponseRemainder(size);
            } catch (const IgotuProtocolError &e) {
                // ignore protocol errors if switched to NMEA mode
                if (d->ignoreProtocolErrors) {
                    if (Verbose::verbose() > 0) {
                        fprintf(stderr, "Command: %s\n",
                                d->command.toHex().data());
                        fprintf(stderr, "Failed protocol (ignored): %s\n",
                                e.what());
                    }
                    return remainder;
                }
                // Assume this was caused by some spurious NMEA messages
                ++protocolErrors;
                if (protocolErrors <= 5) {
                    if (Verbose::verbose() > 0) {
                        fprintf(stderr, "Command: %s\n",
                                d->command.toHex().data());
                        fprintf(stderr, "Failed protocol: %s\n", e.what());
                    }
                    continue;
                }
                throw;
            } catch (const IgotuDeviceError &e) {
                // Device error codes mean we can try again
                ++deviceErrors;
                if (deviceErrors <= 3) {
                    if (Verbose::verbose() > 0) {
                        fprintf(stderr, "Command: %s\n",
                                d->command.toHex().data());
                        fprintf(stderr, "Device failure: %s\n", e.what());
                    }
                    continue;
                }
                throw;
            }

            if (Verbose::verbose() > 0) {
                fprintf(stderr, "Command: %s\n", d->command.toHex().data());
                fprintf(stderr, "Result size: 0x%04x\n", size);
                fprintf(stderr, "Result data: %s\n", remainder.toHex().data());
            }
            return remainder;
        }
    } catch (const std::exception &e) {
        if (Verbose::verbose() > 0) {
            fprintf(stderr, "Command: %s\n", d->command.toHex().data());
            fprintf(stderr, "Failed: %s\n", e.what());
        }
        throw;
    }
}

} // namespace igotu
