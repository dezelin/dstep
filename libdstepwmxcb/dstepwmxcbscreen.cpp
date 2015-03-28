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

#include "dstepwmxcbobjectfactory.h"
#include "dstepwmxcbscreen.h"

#include <QDebug>

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
        q_ptr(parent), m_xcb(xcb), m_xcbScreen(screen)
    {
        Q_ASSERT(m_xcb);
        Q_ASSERT(m_xcbScreen);
    }

    ~DstepWmXcbScreenPrivate()
    {
        qDeleteAll(m_workspaces);
        qDeleteAll(m_depths);
    }

    int init()
    {
        Q_ASSERT(m_xcb);
        Q_ASSERT(m_xcbScreen);

        int ret;
        if ((ret = initScreen(m_xcbScreen)) < 0) {
            qDebug() << "Error parsing xcb screen object, err:" << ret;
            return ret;
        }

        if ((ret = initWorkspaces()) < 0) {
            qDebug() << "Error initializing workspaces, err:" << ret;
            return ret;
        }

        return ret;
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
        return m_virtualGeom;
    }

    const QRect &geometryInMillimeters() const
    {
        return m_geomMM;
    }

private:
    int initScreen(const xcb_screen_t *screen)
    {
        Q_Q(DstepWmXcbScreen);

        Q_ASSERT(m_xcb);
        Q_ASSERT(screen);

        int ret;
        if ((ret = initScreenColormap(screen)) < 0) {
            qDebug() << "Can't initialize screen colormap, err:" << ret;
            return ret;
        }

        if ((ret = initScreenDepths(screen)) < 0) {
            qDebug() << "Can't enumerate screen depths, err:" << ret;
            return ret;
        }

        if ((ret = initScreenGeometry(screen)) < 0) {
            qDebug() << "Can't initialize screen geometry, err:" << ret;
            return ret;
        }

        // Instantiate window and set it's parent to this QObject
        QScopedPointer<Window> rootWindow(
            DstepWmXcbObjectFactoryInstance.createWindow(m_xcb, screen->root, q));
        if (!rootWindow) {
            qDebug() << "Can't instantiate window instance.";
            return -1;
        }

        m_root.swap(rootWindow);
        return 0;
    }

    int initScreenColormap(const xcb_screen_t *screen)
    {
        Q_ASSERT(screen);
        //TODO: Implement support for 256 color screens
        return 0;
    }

    int initScreenDepths(const xcb_screen_t * screen)
    {
        Q_ASSERT(screen);
        m_xcb->foreachScreenDepth(screen, [this](const xcb_depth_t *depth) {
            Q_ASSERT(depth);
            if (!depth)
                return true;

            const xcb_visualtype_t *visual = xcb_depth_visuals(depth);
            QScopedPointer<Colormap> colormap(DstepWmXcbObjectFactoryInstance.createColormap(visual));
            if (!colormap) {
                qDebug() << "Error instantiating colormap object.";
                return true;
            }

            int ret;
            if ((ret = colormap->init()) < 0) {
                qDebug() << "Error initializing colormap for depth" << depth->depth
                         << " , err:" << ret;
                return true;
            }

            m_depths.append(colormap.take());
            return true;
        });

        return 0;
    }

    int initScreenGeometry(const xcb_screen_t *screen)
    {
        Q_ASSERT(screen);
        m_geom = m_virtualGeom = QRect(0, 0, screen->width_in_pixels,
            screen->height_in_pixels);
        m_geomMM = QRect(0, 0, screen->width_in_millimeters,
            screen->height_in_millimeters);
        return 0;
    }

    int initWorkspaces()
    {
        QScopedPointer<Workspace> workspace(
            DstepWmXcbObjectFactoryInstance.createWorkspace());
        if (!workspace) {
            qDebug() << "Error instantiating workspace object.";
            return -1;
        }

        m_workspaces.append(workspace.take());
        return 0;
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbScreen)

    QSharedPointer<DstepWmXcb> m_xcb;
    QScopedPointer<Window> m_root;
    QList<Workspace*> m_workspaces;
    QScopedPointer<Colormap> m_colormap;
    QList<Colormap*> m_depths;
    QRect m_geom;
    QRect m_virtualGeom;
    QRect m_geomMM;

    const xcb_screen_t *m_xcbScreen;
};

DstepWmXcbScreen::DstepWmXcbScreen(QSharedPointer<DstepWmXcb> xcb,
    const xcb_screen_t *screen, QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbScreenPrivate(this, xcb, screen))
{
}

int DstepWmXcbScreen::init()
{
    Q_D(DstepWmXcbScreen);
    return d->init();
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
