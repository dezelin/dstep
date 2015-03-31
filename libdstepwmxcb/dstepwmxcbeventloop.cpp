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

#include "dstepwmxcbeventloop.h"

#include <dstepdebug.h>

#include <QDebug>
#include <QObject>

#include <xcb/xcb.h>

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbEventLoop::DstepWmXcbEventLoopPrivate
{
public:
    DstepWmXcbEventLoopPrivate(DstepWmXcbEventLoop *parent,
        QSharedPointer<DstepWmXcb> xcb) :
        q_ptr(parent), m_xcb(xcb)
    {
        Q_ASSERT(parent);
    }

    int run()
    {
        xcb_generic_event_t *event;
        while ((event = m_xcb->waitForEvent()) != 0) {
            qDebug().noquote() << "Received event of type:" <<
                dstep::misc::hex(event->response_type);
            handleEvent(event);
            free(event);
        }

        return 0;
    }

private:
    int handleEvent(const xcb_generic_event_t *event)
    {
        Q_ASSERT(event);

        return 0;
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbEventLoop)

    QSharedPointer<DstepWmXcb> m_xcb;
};

DstepWmXcbEventLoop::DstepWmXcbEventLoop(QSharedPointer<DstepWmXcb> xcb,
    QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbEventLoopPrivate(this, xcb))
{
}

int DstepWmXcbEventLoop::run()
{
    Q_D(DstepWmXcbEventLoop);
    return d->run();
}

} // namespace wm
} // namespace dstep
