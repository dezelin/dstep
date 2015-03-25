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

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "eventloop.h"
#include "windowdecorator.h"
#include "windowmanager.h"
#include "windowtheme.h"

#include <QObject>
#include <QtPlugin>

namespace dstep
{
namespace wm
{
namespace interfaces
{

class ObjectFactory
{
public:
    virtual ~ObjectFactory()
    {
    }

    virtual EventLoop *createEventLoop() const = 0;
    virtual WindowDecorator *createWindowDecorator(WindowTheme *theme) const = 0;
    virtual WindowManager *createWindowManager() const = 0;
    virtual WindowTheme *createWindowTheme() const = 0;
};

} // namespace interfaces
} // namespace wm
} // namespace dstep

#define ObjectFactory_iid "org.dstep.wm.interfaces.ObjectFactory/1.0"
Q_DECLARE_INTERFACE(dstep::wm::interfaces::ObjectFactory, ObjectFactory_iid)

#endif // OBJECTFACTORY_H
