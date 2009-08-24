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

#include "updatenotification.h"

#include <QSettings>

class UpdateNotificationPrivate : public QObject
{
    Q_OBJECT

    QString releaseUrl() const;

public:
    UpdateNotification *p;
};

// UpdateNotificationPrivate ===================================================

QString UpdateNotificationPrivate::releaseUrl() const
{
    return QSettings().contains(QLatin1String("releaseUrl")) ?
        QSettings().value(QLatin1String("releaseUrl")).toString() :
        QLatin1String("http://mh21.de/igotu2gpx/releases.txt");
}

// UpdateNotification ==========================================================

UpdateNotification::UpdateNotification(QWidget *parent) :
    QMessageBox(parent),
    d(new UpdateNotificationPrivate)
{
    d->p = this;

//    http->get(d->releaseUrl().toEncoded());
}

UpdateNotification::~UpdateNotification()
{
}

#include "updatenotification.moc"