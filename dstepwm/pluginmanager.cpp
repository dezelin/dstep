//
// Copyright (c) 2015 Aleksandar Dezelin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

#include "pluginmanager.h"

#include <dstepwmpimpl.h>
#include <dstepwmplugin.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QLibraryInfo>
#include <QObject>
#include <QPluginLoader>

namespace dstep
{
namespace wm
{

#define DSTEPWM_PLUGINS_SUBDIR "dstepwm"


class PluginManager::PluginManagerPrivate
{
public:
    PluginManagerPrivate(PluginManager *parent) :
        q_ptr(parent)
    {
    }

    void setPlugin(QObject *plugin)
    {
        m_plugin.reset(plugin);
    }

    const QObject *plugin() const
    {
        return m_plugin.data();
    }

private:
    DSTEPWM_DECLARE_PUBLIC(PluginManager)
    QScopedPointer<QObject> m_plugin;
};


PluginManager::PluginManager(QObject *parent) :
    QObject(parent),
    d_ptr(new PluginManagerPrivate(this))
{
}

PluginManager::~PluginManager()
{
    Q_D(PluginManager);
    delete d;
}

int PluginManager::loadPlugins()
{
    Q_D(PluginManager);
    QStringList libraryPaths = QCoreApplication::libraryPaths();
    foreach (QString path, libraryPaths) {
        QDir pluginsDir(path);
        pluginsDir.cd(DSTEPWM_PLUGINS_SUBDIR);
        qDebug() << "Searching for plugins in" << pluginsDir.absolutePath();
        foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
            qDebug() << "Trying to load plugin from" << pluginsDir.absolutePath() + "/" + fileName;
            QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = loader.instance();
            if (!plugin)
                continue;

            DstepWmPlugin *dstepPlugin = qobject_cast<DstepWmPlugin*>(plugin);
            if (!dstepPlugin)
                continue;

            d->setPlugin(plugin);
            qDebug() << "DstepWmPlugin succesfully loaded!";
            break;
        }

        if (!d->plugin())
            continue;

        break;
    }

    return 0;
}

ObjectFactory *PluginManager::createObjectFactory() const
{
    Q_D(const PluginManager);
    Q_ASSERT(d->plugin());
    const DstepWmPlugin *dstepPlugin = qobject_cast<DstepWmPlugin*>(d->plugin());
    Q_ASSERT(dstepPlugin);
    return dstepPlugin->createObjectFactory();
}

} // namespace wm
} // namespace dstep
