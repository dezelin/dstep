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

#include "dstepwmxcbwindowdecorator.h"

#include <dsteppimpl.h>
#include <windowtheme.h>

#include <QObject>

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbWindowDecorator::DstepWmXcbWindowDecoratorPrivate
{
public:
    DstepWmXcbWindowDecoratorPrivate(DstepWmXcbWindowDecorator *parent) :
        q_ptr(parent)
    {
    }

    WindowTheme *theme() const
    {
        return m_theme.data();
    }

    void setTheme(WindowTheme *theme)
    {
        m_theme.reset(theme);
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbWindowDecorator)
    QScopedPointer<WindowTheme> m_theme;
};

DstepWmXcbWindowDecorator::DstepWmXcbWindowDecorator(QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbWindowDecoratorPrivate(this))
{
}

WindowTheme *DstepWmXcbWindowDecorator::theme() const
{
    Q_D(const DstepWmXcbWindowDecorator);
    return d->theme();
}

void DstepWmXcbWindowDecorator::setTheme(WindowTheme *theme)
{
    Q_ASSERT(theme);
    Q_D(DstepWmXcbWindowDecorator);
    d->setTheme(theme);
}

} // namespace wm
} // namespace dstep
