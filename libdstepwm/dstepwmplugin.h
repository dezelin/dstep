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

#ifndef DSTEPWMPLUGIN_H
#define DSTEPWMPLUGIN_H

#include "objectfactory.h"

#include <QtPlugin>

namespace dstep
{
namespace wm
{
namespace interfaces
{

class DstepWmPlugin
{
public:
    virtual ~DstepWmPlugin()
    {
    }

    virtual ObjectFactory *createObjectFactory(QObject *parent = 0) const = 0;

signals:

public slots:

};

} // namespace interfaces
} // namespace wm
} // namespace dstep

#define DstepWmPlugin_iid "org.dstep.wm.interfaces.DstepWmPlugin/1.0"
Q_DECLARE_INTERFACE(dstep::wm::interfaces::DstepWmPlugin, DstepWmPlugin_iid)

#endif // DSTEPWMPLUGIN_H
