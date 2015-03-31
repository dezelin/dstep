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

#include "dstepwmxcbwindowmanager.h"
#include "dstepwmxcb.h"

#include <display.h>
#include <dsteppimpl.h>
#include <dstepwmxcbobjectfactory.h>

#include <QDebug>
#include <QScopedPointer>

#include <xcb/xcb.h>

namespace dstep
{
namespace wm
{

class DstepWmXcbWindowManager::DstepWmXcbWindowManagerPrivate
{
public:
    DstepWmXcbWindowManagerPrivate(DstepWmXcbWindowManager *parent)
        : q_ptr(parent)
    {
    }

    ~DstepWmXcbWindowManagerPrivate()
    {
    }

    int init()
    {
        QScopedPointer<DstepWmXcbObjectFactory> fac(new DstepWmXcbObjectFactory);
        if (!fac) {
            qDebug() << "Can't instantiate object factory.";
            return -1;
        }

        QScopedPointer<Display> display(fac->createDisplay());
        if (!display) {
            qDebug() << "Can't instantiate display object.";
            return -1;
        }

        int err;
        if ((err = display->init()) < 0) {
            qDebug() << "Error initializing display, err:" << err;
            return err;
        }

        m_display.swap(display);
        return err;
    }

    int run()
    {
        Q_ASSERT(m_display);
        return m_display->run();
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbWindowManager)
    QScopedPointer<Display> m_display;
};

DstepWmXcbWindowManager::DstepWmXcbWindowManager(QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbWindowManagerPrivate(this))
{
}

DstepWmXcbWindowManager::~DstepWmXcbWindowManager()
{
    Q_D(DstepWmXcbWindowManager);
    delete d;
}

int DstepWmXcbWindowManager::init()
{
    Q_D(DstepWmXcbWindowManager);
    return d->init();
}

int DstepWmXcbWindowManager::run()
{
    Q_D(DstepWmXcbWindowManager);
    return d->run();
}

} // namespace wm
} // namespace dstep
