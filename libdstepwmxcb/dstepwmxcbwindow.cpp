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

#include "dstepwmxcbwindow.h"

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbWindow::DstepWmXcbWindowPrivate
{
public:
    DstepWmXcbWindowPrivate(DstepWmXcbWindow *parent,
        QSharedPointer<DstepWmXcb> xcb, xcb_window_t windowId) :
        q_ptr(parent), m_xcb(xcb), m_windowId(windowId)
    {

    }

    int init()
    {
        return -1;
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbWindow)

    QSharedPointer<DstepWmXcb> m_xcb;

    xcb_window_t m_windowId;
};

DstepWmXcbWindow::DstepWmXcbWindow(QSharedPointer<DstepWmXcb> xcb,
    xcb_window_t windowId, QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbWindowPrivate(this, xcb, windowId))
{
}


int DstepWmXcbWindow::init()
{
    Q_D(DstepWmXcbWindow);
    return d->init();
}

} // namespace wm
} // namespace dstep
