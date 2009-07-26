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

#include "igotu/paths.h"
#include "igotu/threadutils.h"

#include "pluginloader.h"

#include <QDir>
#include <QMap>
#include <QMutex>
#include <QPluginLoader>

using namespace igotu;

// will be pushed to the worker thread
class PluginLoaderWorker : public QObject
{
    Q_OBJECT
public:
    PluginLoaderWorker();

    QList<QObject*> allAvailablePlugins();
    QString pluginPath(const QObject *object);
    QMap<QString, QString> pluginsWithErrors();

    void reloadPlugins();

Q_SIGNALS:
    void pluginsLoaded();

Q_SIGNALS:
    void dispatchBackgroundInitialization();
private Q_SLOTS:
    void backgroundInitialization();

private:
    void initializeLoading();
    void completeLoading();

    bool loadNextPlugin();
    void loadStaticPlugins();
    void insert(const QString &path, QObject *plugin);

    const QStringList nameFilters;

    QStringList pluginDirectories;
    QStringList fileNames;
    QDir dir;

    QMutex lock;

    bool allPluginsLoaded;
    bool staticPluginsLoaded;

    QList<QObject*> plugins;
    QMap<const QObject*, QString> paths;
    QMap<QString, QString> errors;
};

class PluginLoaderPrivate
{
public:
    PluginLoaderPrivate();
    ~PluginLoaderPrivate();

    EventThread thread;
    PluginLoaderWorker worker;
};

Q_GLOBAL_STATIC(PluginLoaderPrivate, pluginLoaderPrivate)

// PluginLoaderWorker ==========================================================

PluginLoaderWorker::PluginLoaderWorker() :
#if defined(Q_OS_LINUX)
    nameFilters(QLatin1String("lib*.so"))
#elif defined(Q_OS_WIN32)
    nameFilters(QLatin1String("*.dll"))
#elif defined(Q_OS_MACX)
    nameFilters(QLatin1String("*.dylib"))
#else
    nameFilters()
#endif
{
    connect(this, SIGNAL(dispatchBackgroundInitialization()),
            this, SLOT(backgroundInitialization()),
            Qt::QueuedConnection);

    initializeLoading();
}

QList<QObject*> PluginLoaderWorker::allAvailablePlugins()
{
    QMutexLocker locker(&lock);

    completeLoading();

    return plugins;
}

QString PluginLoaderWorker::pluginPath(const QObject *object)
{
    QMutexLocker locker(&lock);

    completeLoading();

    return paths.value(object);
}

QMap<QString, QString> PluginLoaderWorker::pluginsWithErrors()
{
    QMutexLocker locker(&lock);

    completeLoading();

    return errors;
}

void PluginLoaderWorker::reloadPlugins()
{
    QMutexLocker locker(&lock);

    initializeLoading();
    emit dispatchBackgroundInitialization();
}

void PluginLoaderWorker::backgroundInitialization()
{
    QMutexLocker locker(&lock);

    completeLoading();
}

// no mutex protection!
void PluginLoaderWorker::initializeLoading()
{
    staticPluginsLoaded = false;
    allPluginsLoaded = false;
    plugins.clear();
    paths.clear();
    errors.clear();
    pluginDirectories = Paths::pluginDirectories();
}

// no mutex protection!
void PluginLoaderWorker::completeLoading()
{
    loadStaticPlugins();
    while (loadNextPlugin()) {
        // empty
    }
}

// no mutex protection!
void PluginLoaderWorker::loadStaticPlugins()
{
    if (staticPluginsLoaded)
        return;

    Q_FOREACH (QObject * const plugin, QPluginLoader::staticInstances())
        insert(QLatin1String("statically linked"), plugin);
    staticPluginsLoaded = true;
}

// no mutex protection!
bool PluginLoaderWorker::loadNextPlugin()
{
    if (allPluginsLoaded)
        return false;

    while (fileNames.isEmpty()) {
        if (pluginDirectories.isEmpty()) {
            allPluginsLoaded = true;
            emit pluginsLoaded();
            return false;
        }
        dir = QDir(pluginDirectories.takeFirst());
        fileNames = dir.entryList(nameFilters, QDir::Files);
    }
    const QString filePath(dir.absoluteFilePath(fileNames.takeFirst()));
    QPluginLoader loader(filePath);
    QObject *plugin = loader.instance();
    if (plugin) {
        insert(filePath, plugin);
    } else {
        errors.insert(filePath, loader.errorString());
    }
    return true;
}

// no mutex protection!
void PluginLoaderWorker::insert(const QString &path, QObject *plugin)
{
    plugins.append(plugin);
    paths.insert(plugin, path);
}

// PluginLoaderPrivate =========================================================

PluginLoaderPrivate::PluginLoaderPrivate()
{
    worker.moveToThread(&thread);
    thread.start(QThread::IdlePriority);
}

PluginLoaderPrivate::~PluginLoaderPrivate()
{
    thread.quit();
    thread.wait();
}

// PluginLoader ================================================================

PluginLoader::PluginLoader(QObject *parent) :
    QObject(parent)
{
    PluginLoaderWorker &worker = pluginLoaderPrivate()->worker;
    connect(&worker, SIGNAL(pluginsLoaded()), this, SIGNAL(pluginsLoaded()),
            Qt::QueuedConnection);
}

PluginLoader::~PluginLoader()
{
}

QList<QObject*> PluginLoader::allAvailablePlugins()
{
    return pluginLoaderPrivate()->worker.allAvailablePlugins();
}

QString PluginLoader::pluginPath(const QObject *plugin) const
{
    return pluginLoaderPrivate()->worker.pluginPath(plugin);
}

QMap<QString, QString> PluginLoader::pluginsWithErrors() const
{
    return pluginLoaderPrivate()->worker.pluginsWithErrors();
}

void PluginLoader::reloadPlugins()
{
    return pluginLoaderPrivate()->worker.reloadPlugins();
}

#include "pluginloader.moc"
