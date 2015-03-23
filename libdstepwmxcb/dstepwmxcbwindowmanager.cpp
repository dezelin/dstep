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

#include <dsteppimpl.h>
#include <eventloop.h>
#include <windowdecorator.h>

#include <QDebug>

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
        DstepWmXcbInstance.closeConnection();
    }

    int init()
    {
        int ret;
        if ((ret = initDisplay()) != 0)
            return ret;
    }

    int initDisplay()
    {
        int ret;
        if ((ret = DstepWmXcbInstance.openConnection()) != 0) {
            qDebug() << "Can't open X connection to display, err:" << ret;
            return -ret;
        }

        int i = 0;
        qDebug() << "Screen count is" << DstepWmXcbInstance.screenCount();
        DstepWmXcbInstance.foreachScreen([&i](const xcb_screen_t *screen) -> bool {
            qDebug() << "Enumerating screen" << i++;

            return true;
        });

        return ret;
    }

    int initScreen(int screen)
    {

    }

    EventLoop *eventLoop() const
    {
        return m_eventLoop.data();
    }

    void setEventLoop(EventLoop *eventLoop)
    {
        m_eventLoop.reset(eventLoop);
    }

    WindowDecorator *decorator() const
    {
        return m_decorator.data();
    }

    void setDecorator(WindowDecorator *decorator)
    {
        m_decorator.reset(decorator);
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbWindowManager)

    QScopedPointer<EventLoop> m_eventLoop;
    QScopedPointer<WindowDecorator> m_decorator;
};

DstepWmXcbWindowManager::DstepWmXcbWindowManager(QObject *parent) :
    QObject(parent),
    d_ptr(new DstepWmXcbWindowManagerPrivate(this))
{
}

DstepWmXcbWindowManager::~DstepWmXcbWindowManager()
{
    Q_D(DstepWmXcbWindowManager);
    delete d;
}

EventLoop *DstepWmXcbWindowManager::eventLoop() const
{
    Q_D(const DstepWmXcbWindowManager);
    return d->eventLoop();
}

void DstepWmXcbWindowManager::setEventLoop(EventLoop *eventLoop)
{
    Q_D(DstepWmXcbWindowManager);
    d->setEventLoop(eventLoop);
}

WindowDecorator *DstepWmXcbWindowManager::decorator() const
{
    Q_D(const DstepWmXcbWindowManager);
    return d->decorator();
}

void DstepWmXcbWindowManager::setWindowDecorator(WindowDecorator *decorator)
{
    Q_D(DstepWmXcbWindowManager);
    d->setDecorator(decorator);
}

int DstepWmXcbWindowManager::run()
{
    Q_D(DstepWmXcbWindowManager);

    int ret;
    if ((ret = d->init()) < 0)
        return ret;

    Q_ASSERT(d->eventLoop());
    return d->eventLoop()->run();
}

} // namespace wm
} // namespace dstep
