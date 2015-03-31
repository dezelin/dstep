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

#include "dstepwmxcb.h"
#include "dstepwmxcbdisplay.h"
#include "dstepwmxcbobjectfactory.h"

#include <QDebug>
#include <QList>
#include <QObject>
#include <QSharedPointer>

#include <xcb/xcb.h>

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbDisplay::DstepWmXcbDisplayPrivate
{
public:
    DstepWmXcbDisplayPrivate(DstepWmXcbDisplay *parent) :
        q_ptr(parent), m_xcb(DstepWmXcbObjectFactoryInstance.createXcbAdapter())
    {
    }

    ~DstepWmXcbDisplayPrivate()
    {
        closeXcbConnection();
        qDeleteAll(m_screens);
    }

    int init()
    {
        int err;
        if ((err = initXcb()) < 0) {
            qDebug() << "Can't create xcb adapter instance, err:" << err;
            return err;
        }

        if ((err = openXcbConnection()) < 0) {
            qDebug() << "Can't open connection to default display, err:" << err;
            return err;
        }

        if ((err = initEventLoop()) < 0) {
            qDebug() << "Error initializing event loop, err:" << err;
            return err;
        }

        int i = 0;
        m_xcb->foreachScreen([this, &i](const xcb_screen_t *screen) {
            Q_ASSERT(screen);
            if (!screen)
                return true;

            qDebug() << "Enumerating screen" << i++;
            QScopedPointer<Screen> dstepScreen(
                DstepWmXcbObjectFactoryInstance.createScreen(m_xcb, screen));
            if (!dstepScreen) {
                qDebug() << "Can't create screen instance.";
                return true;
            }

            if (dstepScreen->init() < 0)
                return true;

            m_screens.append(dstepScreen.take());
            return true;
        });

        return err;
    }

    int run()
    {
        Q_ASSERT(m_eventLoop);
        return m_eventLoop->run();
    }

    const QList<Screen*> &screens() const
    {
        return m_screens;
    }

private:
    int initEventLoop()
    {
        Q_ASSERT(m_xcb);
        QScopedPointer<EventLoop> eventLoop(
            DstepWmXcbObjectFactoryInstance.createEventLoop(m_xcb));
        if (!eventLoop)
            return -1;

        m_eventLoop.swap(eventLoop);
        return 0;
    }

    int initXcb()
    {
        Q_ASSERT(m_xcb);
        return m_xcb->init();
    }

    void closeXcbConnection()
    {
        Q_ASSERT(m_xcb);
        m_xcb->closeConnection();
    }

    int openXcbConnection()
    {
        Q_ASSERT(m_xcb);
        return m_xcb->openConnection();
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbDisplay)
    QSharedPointer<DstepWmXcb> m_xcb;
    QScopedPointer<EventLoop> m_eventLoop;
    QList<Screen*> m_screens;
};

DstepWmXcbDisplay::DstepWmXcbDisplay(QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbDisplayPrivate(this))
{
}

int DstepWmXcbDisplay::init()
{
    Q_D(DstepWmXcbDisplay);
    return d->init();
}

int DstepWmXcbDisplay::run()
{
    Q_D(DstepWmXcbDisplay);
    return d->run();
}

const QList<Screen *> &DstepWmXcbDisplay::screens() const
{
    Q_D(const DstepWmXcbDisplay);
    return d->screens();
}

} // namespace wm
} // namespace dstep
