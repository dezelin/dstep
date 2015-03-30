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

#include <dsteppimpl.h>

#include <QList>

#include <xcb/xcb.h>

namespace dstep
{
namespace wm
{

class DstepWmXcb::DstepWmXcbPrivate
{
public:
    DstepWmXcbPrivate(DstepWmXcb *parent) :
        q_ptr(parent)
    {
    }

    ~DstepWmXcbPrivate()
    {
        closeConnection();
    }

    int init()
    {
        return 0;
    }

    int openConnection()
    {
        Q_Q(DstepWmXcb);

        int err = 0;
        if ((m_conn = xcb_connect(0, 0)) == 0) {
            q->error(-1);
            return -1;
        }

        if ((err = xcb_connection_has_error(m_conn)) != 0) {
            closeConnection();
            q->error(-err);
        }

        return -err;
    }

    void closeConnection()
    {
        Q_ASSERT(m_conn);
        xcb_disconnect(m_conn);
    }

    template<typename Func>
    void foreachScreen(Func f) const
    {
        Q_ASSERT(m_conn);
        xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_get_setup(m_conn));
        for(; iter.rem; xcb_screen_next(&iter)) {
            if (!f(const_cast<const xcb_screen_t*>(iter.data)))
                break;
        }
    }

    template<typename Func>
    void foreachScreenDepth(const xcb_screen_t *screen, Func f) const
    {
        Q_ASSERT(m_conn);
        Q_ASSERT(screen);
        if (!screen)
            return;

        xcb_depth_iterator_t iter = xcb_screen_allowed_depths_iterator(screen);
        for(; iter.rem; xcb_depth_next(&iter)) {
            if (!f(const_cast<const xcb_depth_t*>(iter.data)))
                break;
        }
    }

    template<typename Func>
    void foreachScreenWindow(const xcb_screen_t *screen, Func f) const
    {
        Q_ASSERT(m_conn);
        Q_ASSERT(screen);
        if (!screen)
            return;

        xcb_query_tree_reply_t *reply;
        xcb_query_tree_cookie_t cookie = xcb_query_tree(m_conn, screen->root);
        if ((reply = xcb_query_tree_reply(m_conn, cookie, 0)) != 0) {
            xcb_window_t *children = xcb_query_tree_children(reply);
            for (int i = 0; i < xcb_query_tree_children_length(reply); ++i)
                if (!f(children[i]))
                    break;
        }
    }

    const xcb_visualtype_t *getVisualFromDepth(const xcb_depth_t *depth) const
    {
        Q_ASSERT(depth);
        if (!depth)
            return 0;

        return xcb_depth_visuals(depth);
    }

    int reparentWindow(xcb_window_t handle, xcb_window_t parent) const
    {
        // Get window coordinates relative to the root window.
        // We don't have to translate them as we are working only with top level windows.
        int errCode = 0;
        xcb_generic_error_t *err = 0;
        xcb_get_geometry_cookie_t geomCookie = xcb_get_geometry(m_conn, handle);
        xcb_get_geometry_reply_t *geomReply = xcb_get_geometry_reply(m_conn, geomCookie, &err);
        Q_ASSERT(!err);
        Q_ASSERT(geomReply->root == parent);
        if (!err) {
            Q_ASSERT(geomReply);
            xcb_void_cookie_t reparentCookie = xcb_reparent_window_checked(m_conn,
                handle, parent, geomReply->x, geomReply->y);
            if ((err = xcb_request_check(m_conn, reparentCookie)) != 0)
                errCode = err->error_code;
        } else
            errCode = err->error_code;

        free(err);
        return errCode;
    }

    int screenCount() const
    {
        Q_ASSERT(m_conn);
        return xcb_setup_roots_length(xcb_get_setup(m_conn));
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcb)

    xcb_connection_t *m_conn;
};

DstepWmXcb::DstepWmXcb(QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbPrivate(this))
{
}

int DstepWmXcb::init()
{
    Q_D(DstepWmXcb);
    return d->init();
}

int DstepWmXcb::openConnection()
{
    Q_D(DstepWmXcb);
    return d->openConnection();
}

void DstepWmXcb::closeConnection()
{
    Q_D(DstepWmXcb);
    d->closeConnection();
}

void DstepWmXcb::foreachScreen(ForeachScreenFunctor f) const
{
    Q_D(const DstepWmXcb);
    d->foreachScreen(f);
}

void DstepWmXcb::foreachScreenDepth(const xcb_screen_t *screen,
    DstepWmXcb::ForeachScreenDepthFunctor f) const
{
    Q_D(const DstepWmXcb);
    d->foreachScreenDepth(screen, f);
}

void DstepWmXcb::foreachScreenWindow(const xcb_screen_t *screen,
    DstepWmXcb::ForeachScreenWindowFunctor f) const
{
    Q_D(const DstepWmXcb);
    d->foreachScreenWindow(screen, f);
}

const xcb_visualtype_t *DstepWmXcb::getVisualFromDepth(const xcb_depth_t *depth) const
{
    Q_D(const DstepWmXcb);
    return d->getVisualFromDepth(depth);
}

int DstepWmXcb::reparentWindow(xcb_window_t windowId, xcb_window_t parentId) const
{
    Q_D(const DstepWmXcb);
    return d->reparentWindow(windowId, parentId);
}

int DstepWmXcb::screenCount() const
{
    Q_D(const DstepWmXcb);
    return d->screenCount();
}

} // namespace wm
} // namespace dstep
