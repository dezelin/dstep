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

#ifndef DSTEPWMXCBEVENTLOOP_H
#define DSTEPWMXCBEVENTLOOP_H

#include "dstepwmxcb.h"

#include <dsteppimpl.h>
#include <eventloop.h>

#include <QObject>

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbEventLoop : public QObject, public EventLoop
{
    Q_OBJECT
    Q_INTERFACES(dstep::wm::interfaces::EventLoop)
public:
    explicit DstepWmXcbEventLoop(QSharedPointer<DstepWmXcb> xcb,
        QObject *parent = 0);

signals:

public slots:

    // EventLoop interface
public:
    int run();

private:
    DSTEP_DECLARE_PRIVATE(DstepWmXcbEventLoop)
};

} // namespace wm
} // namespace dstep

#endif // DSTEPWMXCBEVENTLOOP_H
