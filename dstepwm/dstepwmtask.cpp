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

#include <dstepwmpimpl.h>
#include <windowmanager.h>

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
        return 0;
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

        m_wm.reset(fac->createWindowManager());
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
    DSTEPWM_DECLARE_PUBLIC(DstepWmTask);
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
