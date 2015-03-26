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
#include "dstepwmxcbdisplay.h"
#include "dstepwmxcbobjectfactory.h"

#include <QDebug>
#include <QObject>
#include <QScopedPointer>

#include <xcb/xcb.h>

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbDisplay::DstepWmXcbDisplayPrivate
{
public:
    DstepWmXcbDisplayPrivate(DstepWmXcbDisplay *parent) :
        q_ptr(parent)
    {

    }

    ~DstepWmXcbDisplayPrivate()
    {
        destroyScreens();
        closeConnection();
    }

    int init()
    {
        int ret;
        if ((ret = openConnection()) < 0)
            return ret;

        int i = 0;
        DstepWmXcbInstance.foreachScreen([this, &i](const xcb_screen_t *screen) {
            Q_ASSERT(screen);
            if (!screen)
                return true;

            qDebug() << "Enumerating screen" << i++;
            QScopedPointer<Screen> scr(parseXcbScreen(screen));
            if (!scr) {
                qDebug() << "Can't create screen instance.";
                return true;
            }

            m_screens.append(scr.take());
            return true;
        });

        return ret;
    }

    void closeConnection()
    {
        DstepWmXcbInstance.closeConnection();
    }

    int openConnection()
    {
        int ret;
        if ((ret = DstepWmXcbInstance.openConnection()) < 0) {
            qDebug() << "Can't open connection to default display, err:" << ret;
            return ret;
        }

        return ret;
    }

    const Display::ScreenList &screens() const
    {
        return m_screens;
    }

private:
    void destroyScreens()
    {
        foreach (Screen *screen, m_screens) {
            Q_ASSERT(screen);
            delete screen;
        }

        m_screens.clear();
    }

    Screen *parseXcbScreen(const xcb_screen_t *screen)
    {
        return 0;
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbDisplay)
    Display::ScreenList m_screens;
};

DstepWmXcbDisplay::DstepWmXcbDisplay(QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbDisplayPrivate(this))
{
}

int DstepWmXcbDisplay::init()
{
    return -1;
}

const Display::ScreenList &DstepWmXcbDisplay::screens() const
{
    Q_D(const DstepWmXcbDisplay);
    return d->screens();
}


} // namespace wm
} // namespace dstep
