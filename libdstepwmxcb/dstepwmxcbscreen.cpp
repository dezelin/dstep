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

#include "dstepwmxcbscreen.h"

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbScreen::DstepWmXcbScreenPrivate
{
public:
    DstepWmXcbScreenPrivate(DstepWmXcbScreen *parent,
        QSharedPointer<DstepWmXcb> xcb, const xcb_screen_t *screen) :
        m_xcb(xcb), q_ptr(parent)
    {
        Q_ASSERT(m_xcb);
        Q_ASSERT(screen);
        prepare(screen);
    }

    ~DstepWmXcbScreenPrivate()
    {
        qDeleteAll(m_workspaces);
        qDeleteAll(m_depths);
    }

    Window *rootWindow() const
    {
        return m_root.data();
    }

    void setRootWindow(Window *window)
    {
        m_root.reset(window);
    }

    const QList<Workspace*> &workspaces() const
    {
        return m_workspaces;
    }

    Colormap *colormap() const
    {
        return m_colormap.data();
    }

    void setColormap(Colormap *colormap)
    {
        m_colormap.reset(colormap);
    }

    const QList<Colormap*> &depths() const
    {
        return m_depths;
    }

    const QRect &geometry() const
    {
        return m_geom;
    }

    const QRect &virtualGeometry() const
    {
        return m_virtGeom;
    }

    const QRect &geometryInMillimeters() const
    {
        return m_geomMM;
    }

private:
    void prepare(const xcb_screen_t *screen)
    {
        Q_ASSERT(screen);
    }

private:
    QSharedPointer<DstepWmXcb> m_xcb;
    QScopedPointer<Window> m_root;
    QList<Workspace*> m_workspaces;
    QScopedPointer<Colormap> m_colormap;
    QList<Colormap*> m_depths;
    QRect m_geom;
    QRect m_virtGeom;
    QRect m_geomMM;

    DSTEP_DECLARE_PUBLIC(DstepWmXcbScreen)
};

DstepWmXcbScreen::DstepWmXcbScreen(QSharedPointer<DstepWmXcb> xcb,
    const xcb_screen_t *screen, QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbScreenPrivate(this, xcb, screen))
{
}

Window *DstepWmXcbScreen::rootWindow() const
{
    Q_D(const DstepWmXcbScreen);
    return d->rootWindow();
}

void DstepWmXcbScreen::setRootWindow(Window *window)
{
    Q_D(DstepWmXcbScreen);
    d->setRootWindow(window);
}

const QList<Workspace *> &DstepWmXcbScreen::workspaces() const
{
    Q_D(const DstepWmXcbScreen);
    return d->workspaces();
}

Colormap *DstepWmXcbScreen::colormap() const
{
    Q_D(const DstepWmXcbScreen);
    return d->colormap();
}

void DstepWmXcbScreen::setColormap(Colormap *colormap)
{
    Q_D(DstepWmXcbScreen);
    d->setColormap(colormap);
}

const QList<Colormap *> &DstepWmXcbScreen::depths() const
{
    Q_D(const DstepWmXcbScreen);
    return d->depths();
}

const QRect &DstepWmXcbScreen::geometry() const
{
    Q_D(const DstepWmXcbScreen);
    return d->geometry();
}

const QRect &DstepWmXcbScreen::virtualGeometry() const
{
    Q_D(const DstepWmXcbScreen);
    return d->virtualGeometry();
}

const QRect &DstepWmXcbScreen::geometryInMillimeters() const
{
    Q_D(const DstepWmXcbScreen);
    return d->geometryInMillimeters();
}

} // namespace wm
} // namespace dstep
