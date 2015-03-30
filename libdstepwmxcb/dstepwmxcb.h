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

#ifndef DSTEPWMXCB_H
#define DSTEPWMXCB_H

#include <dsteppimpl.h>
#include <singleton.h>

#include <QObject>

#include <functional>
#include <xcb/xcb.h>

namespace dstep
{
namespace wm
{

class DstepWmXcb : public QObject
{
    Q_OBJECT
public:
    explicit DstepWmXcb(QObject *parent = 0);

signals:
    void error(int errorCode);

public slots:

public:
    int init();
    int openConnection();
    void closeConnection();
    int screenCount() const;

    typedef std::function<bool(const xcb_screen_t*)> ForeachScreenFunctor;
    void foreachScreen(ForeachScreenFunctor f) const;

    typedef std::function<bool(const xcb_depth_t*)> ForeachScreenDepthFunctor;
    void foreachScreenDepth(const xcb_screen_t *screen, ForeachScreenDepthFunctor f) const;

    typedef std::function<bool(const xcb_window_t windowId)> ForeachScreenWindowFunctor;
    void foreachScreenWindow(const xcb_screen_t *screen, ForeachScreenWindowFunctor f) const;

    const xcb_visualtype_t *getVisualFromDepth(const xcb_depth_t *depth) const;

    int reparentWindow(xcb_window_t windowId, xcb_window_t parentId) const;

private:
    DSTEP_DECLARE_PRIVATE(DstepWmXcb)
};


} // namespace wm
} // namespace dstep

#endif // DSTEPWMXCB_H
