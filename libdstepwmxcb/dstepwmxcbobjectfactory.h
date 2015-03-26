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

#ifndef DSTEPWMXCBOBJECTFACTORY_H
#define DSTEPWMXCBOBJECTFACTORY_H

#include <display.h>
#include <eventloop.h>
#include <objectfactory.h>
#include <screen.h>
#include <singleton.h>
#include <windowdecorator.h>
#include <windowmanager.h>
#include <windowtheme.h>

#include <QObject>

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbObjectFactory : public QObject, public ObjectFactory
{
    Q_OBJECT
    Q_INTERFACES(dstep::wm::interfaces::ObjectFactory)
public:
    explicit DstepWmXcbObjectFactory(QObject *parent = 0);

signals:

public slots:

    // ObjectFactory interface
public:
    Display *createDisplay() const;
    EventLoop *createEventLoop() const;
    Screen *createScreen() const;
    WindowDecorator *createWindowDecorator(WindowTheme *theme) const;
    WindowManager *createWindowManager() const;
    WindowTheme *createWindowTheme() const;
};

} // namespace wm
} // namespace dstep

#define DstepWmXcbObjectFactoryInstance \
    dstep::patterns::Singleton<dstep::wm::DstepWmXcbObjectFactory>::instance()

#endif // DSTEPWMXCBOBJECTFACTORY_H
