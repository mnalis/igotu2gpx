/******************************************************************************
 * Copyright (C) 2007  Michael Hofmann <mh21@mh21.de>                         *
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

#ifndef _IGOTU2GPX_SRC_IGOTU_EXCEPTION_H_
#define _IGOTU2GPX_SRC_IGOTU_EXCEPTION_H_

/** @file
 * Exception class declaration.
 */

#include "global.h"

#include <QByteArray>
#include <QString>

namespace igotu
{

/** Exception that provides a simple error message. All derived classes must be
 * marked with IGOTU_EXPORT, otherwise exceptions will just terminate()!
 */
class IGOTU_EXPORT Exception: public std::exception
{
public:
    /** Creates a new instance with the given error message. Please use a
     * meaningful description that makes it possible to isolate the error
     * position. Converts the QString to the local encoding with
     * QString#toLocal8Bit() before saving it as a char array that will be
     * returned by #what().
     *
     * @param message error message
     *
     * @see what()
     */
    Exception(const QString &message) throw() :
        message(message.toLocal8Bit())
    {
    }

    /** Virtual destructor to make the compiler happy. */
    virtual ~Exception() throw()
    {
    }

    /** Returns the error message.
     *
     * @return error message
     */
    virtual const char* what() const throw()
    {
        return message;
    }

private:
    const QByteArray message;
};

/** Exception for igotu protocol errors. These are errors where the device
 * response does not conform to its own protocol.
 */
class IGOTU_EXPORT IgotuProtocolError: public Exception
{
public:
    IgotuProtocolError(const QString &message) throw() :
        Exception(message)
    {
    }
};

/** Exception for igotu device errors. These are errors where the device
 * response correctly, but with an error code.
 */
class IGOTU_EXPORT DeviceException: public Exception
{
public:
    DeviceException(const QString &message) throw() :
        Exception(message)
    {
    }
};

} // namespace igotu

#endif
