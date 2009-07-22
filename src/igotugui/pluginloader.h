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

#ifndef _IGOTU2GPX_SRC_IGOTUGUI_PLUGINLOADER_H_
#define _IGOTU2GPX_SRC_IGOTUGUI_PLUGINLOADER_H_

#include <QMap>
#include <QObject>

class PluginLoader : public QObject
{
    Q_OBJECT
public:
    PluginLoader(QObject *parent = NULL);
    ~PluginLoader();

    QList<QObject*> allAvailablePlugins();
    template <typename T> QList<T*> availablePlugins();

    QString pluginPath(const QObject *plugin) const;
    QMap<QString, QString> pluginsWithErrors() const;

public Q_SLOTS:
    void reloadPlugins();

Q_SIGNALS:
    void pluginsLoaded();
};

template <typename T>
QList<T*> PluginLoader::availablePlugins()
{
    QList<T*> result;

    Q_FOREACH (QObject * const plugin, allAvailablePlugins())
        if (T * const casted = qobject_cast<T*> (plugin))
            result.append(casted);

    return result;
};

#endif

