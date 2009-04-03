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

#include "commands.h"
#include "exception.h"

#include <QtEndian>

namespace igotu
{

// NmeaSwitchCommand ===========================================================

NmeaSwitchCommand::NmeaSwitchCommand(DataConnection *connection, bool enable) :
    IgotuCommand(connection)
{
    QByteArray command(15, 0);
    command.replace(0, 3, "\x93\x01\x01");
    command[3] = enable ? '\x00' : '\x03';
    setCommand(command);

    if (enable)
        setIgnoreProtocolErrors(true);
}

// IdentificationCommand =======================================================

IdentificationCommand::IdentificationCommand(DataConnection *connection) :
    IgotuCommand(connection)
{
    QByteArray command(15, 0);
    command.replace(0, 2, "\x93\x0a");
    setCommand(command);
}

QByteArray IdentificationCommand::sendAndReceive()
{
    // TODO: what are the other 4 bytes?
    const QByteArray result = IgotuCommand::sendAndReceive();
    if (result.size() < 6)
        throw IgotuError(tr("Response too short"));
    id = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>
            (result.data()));
    version = QString().sprintf("%u.%02u",
            *reinterpret_cast<const uchar*>(result.data() + 4),
            *reinterpret_cast<const uchar*>(result.data() + 5));
    switch (*reinterpret_cast<const uchar*>(result.data() + 4)) {
    case 2:
        // GT-100 is model 1, GT-200 is model two
        // TODO: @trip PC can figure it out
        name = QLatin1String("GT-100/GT-200");
        break;
    case 3:
        name = QLatin1String("GT-120");
        break;
    default:
        name = QLatin1String("Unknown model");
        break;
    }
    return result;
}

unsigned IdentificationCommand::serialNumber() const
{
    return id;
}

QString IdentificationCommand::firmwareVersion() const
{
    return version;
}

QString IdentificationCommand::deviceName() const
{
    return name;
}

// CountCommand ================================================================

CountCommand::CountCommand(DataConnection *connection) :
    IgotuCommand(connection)
{
    QByteArray command(15, 0);
    command.replace(0, 3, "\x93\x0b\x03");
    command.replace(4, 1, "\x1d");
    setCommand(command);
}

QByteArray CountCommand::sendAndReceive()
{
    // TODO: what is the first byte?
    const QByteArray result = IgotuCommand::sendAndReceive();
    if (result.size() < 3)
        throw IgotuError(tr("Response too short"));
    count = qFromBigEndian<quint16>(reinterpret_cast<const uchar*>
            (result.data() + 1));
    return result;
}

unsigned CountCommand::trackPointCount() const
{
    return count;
}

// ReadCommand =================================================================

ReadCommand::ReadCommand(DataConnection *connection, unsigned pos,
        unsigned size) :
    IgotuCommand(connection)
{
    QByteArray command(15, 0);
    command.replace(0, 3, "\x93\x05\x07");
    command[3] = (size >> 0x08) & 0xff;
    command[4] = (size >> 0x00) & 0xff;
    command.replace(5, 2, "\x04\x03");
    command[7] = (pos >> 0x10) & 0xff;
    command[8] = (pos >> 0x08) & 0xff;
    command[9] = (pos >> 0x00) & 0xff;
    setCommand(command);
}

QByteArray ReadCommand::sendAndReceive()
{
    return (result = IgotuCommand::sendAndReceive());
}

QByteArray ReadCommand::data() const
{
    return result;
}

// WriteCommand ================================================================

WriteCommand::WriteCommand(DataConnection *connection, unsigned pos,
        const QByteArray &data) :
    IgotuCommand(connection),
    pos(pos),
    contents(data)
{
    QByteArray command(15, 0);
    command.replace(0, 3, "\x93\x06\x07");
    command[3] = (data.size() >> 0x08) & 0xff;
    command[4] = (data.size() >> 0x00) & 0xff;
    command.replace(5, 2, "\x04\x02");
    command[7] = (pos >> 0x10) & 0xff;
    command[8] = (pos >> 0x08) & 0xff;
    command[9] = (pos >> 0x00) & 0xff;
    setCommand(command);
}

QByteArray WriteCommand::sendAndReceive()
{
    IgotuCommand::sendAndReceive();
    for (unsigned i = 0; i < (unsigned(contents.size()) + 6) / 7; ++i)
        IgotuCommand(connection(), contents.mid(i * 7, 7)).sendAndReceive();
    return QByteArray();
}

void WriteCommand::setData(const QByteArray &data)
{
    contents = data;
}

QByteArray WriteCommand::data() const
{
    return contents;
}

void WriteCommand::setPosition(unsigned value)
{
    pos = value;
}

unsigned WriteCommand::position() const
{
    return pos;
}

} // namespace igotu

