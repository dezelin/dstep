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
#include "dstepwmxcbcolormap.h"
#include "dstepwmxcbdisplay.h"
#include "dstepwmxcbeventloop.h"
#include "dstepwmxcbobjectfactory.h"
#include "dstepwmxcbscreen.h"
#include "dstepwmxcbwindow.h"
#include "dstepwmxcbwindowdecorator.h"
#include "dstepwmxcbwindowmanager.h"
#include "dstepwmxcbwindowtheme.h"
#include "dstepwmxcbworkspace.h"

#include <QSharedPointer>

namespace dstep
{
namespace wm
{

DstepWmXcbObjectFactory::DstepWmXcbObjectFactory(QObject *parent) :
    QObject(parent)
{
}

Display *DstepWmXcbObjectFactory::createDisplay() const
{
    return new DstepWmXcbDisplay;
}

EventLoop *DstepWmXcbObjectFactory::createEventLoop() const
{
    return new DstepWmXcbEventLoop;
}

Screen *DstepWmXcbObjectFactory::createScreen(QSharedPointer<DstepWmXcb> xcb,
    const xcb_screen_t *screen) const
{
    return new DstepWmXcbScreen(xcb, screen);
}

Window *DstepWmXcbObjectFactory::createWindow(QSharedPointer<DstepWmXcb> xcb,
    xcb_window_t windowId, Window *parent) const
{
    return new DstepWmXcbWindow(xcb, windowId, parent);
}

Window *DstepWmXcbObjectFactory::createWindow(QSharedPointer<DstepWmXcb> xcb,
    xcb_window_t windowId, QObject *parent) const
{
    return new DstepWmXcbWindow(xcb, windowId, parent);
}

WindowDecorator *DstepWmXcbObjectFactory::createWindowDecorator() const
{
    return new DstepWmXcbWindowDecorator;
}

WindowManager *DstepWmXcbObjectFactory::createWindowManager() const
{
    return new DstepWmXcbWindowManager;
}

Colormap *DstepWmXcbObjectFactory::createColormap(const xcb_visualtype_t *visual, int depth) const
{
    return new DstepWmXcbColormap(visual, depth);
}

WindowTheme *DstepWmXcbObjectFactory::createWindowTheme() const
{
    return new DstepWmXcbWindowTheme;
}

Workspace *DstepWmXcbObjectFactory::createWorkspace() const
{
    return new DstepWmXcbWorkspace;
}

DstepWmXcb *DstepWmXcbObjectFactory::createXcbAdapter() const
{
    return new DstepWmXcb;
}

} // namespace wm
} // namespace dstep
