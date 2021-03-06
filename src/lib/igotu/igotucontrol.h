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

#ifndef _IGOTU2GPX_SRC_IGOTU_IGOTUCONTROL_H_
#define _IGOTU2GPX_SRC_IGOTU_IGOTUCONTROL_H_

#include "global.h"

#include <boost/scoped_ptr.hpp>

#include <QObject>
#include <QPair>
#include <QVariantMap>

namespace igotu
{

class IgotuControlPrivate;
class IgotuConfig;

class IGOTU_EXPORT IgotuControl : public QObject
{
    Q_OBJECT
public:
    IgotuControl(QObject *parent = NULL);
    ~IgotuControl();

    // usb:<vendor>:<product>, serial:<n> or image:<base64>
    QString device() const;
    // default device for the platform
    static QString defaultDevice();

    int utcOffset() const;
    static int defaultUtcOffset();

    bool tracksAsSegments() const;
    static bool defaultTracksAsSegments();

    void info();
    void contents();
    void purge();
    void reset();
    void configure(const QVariantMap &config);

    static QList<QPair<const char*, QString> > configureParameters();

    // schedules a slot of an object that will be called when all tasks have
    // been processed
    void notify(QObject *object, const char *method);

    // signals the thread to cancel the currently running operation
    void cancel();

    // Returns true if no tasks are pending
    bool queuesEmpty();

public Q_SLOTS:
    void setDevice(const QString &device);
    void setUtcOffset(int seconds);
    void setTracksAsSegments(bool tracksAsSegments);

Q_SIGNALS:
    void commandStarted(const QString &message);
    // num: 0 to total
    void commandRunning(uint num, uint total);
    void commandFailed(const QString &message);
    void commandSucceeded();

    void infoRetrieved(const QString &info, const QByteArray &contents);
    void contentsRetrieved(const QByteArray &contents, uint count);

protected:
    boost::scoped_ptr<IgotuControlPrivate> d;
};

} // namespace igotu

#endif
