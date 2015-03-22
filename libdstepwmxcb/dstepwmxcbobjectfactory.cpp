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
#include "dstepwmxcbobjectfactory.h"
#include "dstepwmxcbwindowdecorator.h"
#include "dstepwmxcbwindowmanager.h"
#include "dstepwmxcbwindowtheme.h"

#include <QScopedPointer>

namespace dstep
{
namespace wm
{

DstepWmXcbObjectFactory::DstepWmXcbObjectFactory(QObject *parent) :
    QObject(parent)
{
}

EventLoop *DstepWmXcbObjectFactory::createEventLoop() const
{
    return new DstepWmXcbEventLoop;
}

WindowDecorator *DstepWmXcbObjectFactory::createWindowDecorator(WindowTheme *theme) const
{
    QScopedPointer<DstepWmXcbWindowDecorator> decorator(
        new DstepWmXcbWindowDecorator);
    decorator->setTheme(theme);
    return decorator.take();
}

WindowManager *DstepWmXcbObjectFactory::createWindowManager(EventLoop *eventLoop,
    WindowDecorator *decorator) const
{
    QScopedPointer<DstepWmXcbWindowManager> windowManager(
        new DstepWmXcbWindowManager);
    windowManager->setEventLoop(eventLoop);
    windowManager->setWindowDecorator(decorator);
    return windowManager.take();
}

WindowTheme *DstepWmXcbObjectFactory::createWindowTheme() const
{
    return new DstepWmXcbWindowTheme;
}

} // namespace wm
} // namespace dstep
