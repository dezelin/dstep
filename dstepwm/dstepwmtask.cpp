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

#include "dstepwmtask.h"
#include "objectfactory.h"
#include "pluginmanager.h"

#include <dsteppimpl.h>
#include <eventloop.h>
#include <windowdecorator.h>
#include <windowmanager.h>
#include <windowtheme.h>

#include <QCoreApplication>
#include <QPointer>
#include <QScopedPointer>
#include <QtDebug>

namespace dstep
{
namespace wm
{

using namespace interfaces;

class DstepWmTask::DstepWmTaskPrivate
{
public:
    DstepWmTaskPrivate(DstepWmTask *parent) :
        q_ptr(parent),
        m_pm(new PluginManager)
    {
    }

    int init()
    {
        int ret;
        if ((ret = loadPlugins()) < 0)
            return ret;

        if ((ret = initWindowManager()) < 0)
            return ret;

        return 0;
    }

    int run()
    {
        Q_ASSERT(m_wm);
        return m_wm->run();
    }

private:
    int initWindowManager()
    {
        Q_ASSERT(m_pm);

        QScopedPointer<ObjectFactory> fac(m_pm->createObjectFactory());
        if (!fac) {
            qDebug() << "Can't create object factory.";
            return -1;
        }

        QScopedPointer<EventLoop> eventLoop(fac->createEventLoop());
        if (!eventLoop) {
            qDebug() << "Can't create event loop instance.";
            return -1;
        }

        QScopedPointer<WindowTheme> theme(fac->createWindowTheme());
        if (!theme) {
            qDebug() << "Can't create window theme instance.";
            return -1;
        }

        QScopedPointer<WindowDecorator> decorator(fac->createWindowDecorator(theme.take()));
        if (!decorator) {
            qDebug() << "Can't create window decorator instance.";
            return -1;
        }

        m_wm.reset(fac->createWindowManager(eventLoop.take(), decorator.take()));
        if (!m_wm) {
            qDebug() << "Can't create window manager.";
            return -1;
        }

        return 0;
    }

    int loadPlugins()
    {
        Q_ASSERT(m_pm);

        int ret;
        if ((ret = m_pm->loadPlugins()) < 0) {
            qDebug() << "Can't load plugins: " << ret;
            return ret;
        }

        return 0;
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmTask)

    QScopedPointer<PluginManager> m_pm;
    QScopedPointer<WindowManager> m_wm;
};

DstepWmTask::DstepWmTask(QObject *parent) :
    QObject(parent), d_ptr(new DstepWmTaskPrivate(this))
{
    Q_ASSERT(parent);
}

DstepWmTask::~DstepWmTask()
{
    Q_D(DstepWmTask);
    delete d;
}

void DstepWmTask::run()
{
    Q_D(DstepWmTask);

    int ret;
    if ((ret = d->init()) == 0)
        ret = d->run();

    finished(-ret);
}

} // namespace wm
} // namespace dstep
