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

#include <dstepwmpimpl.h>

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

    }

    int init()
    {
        int ret;
        if ((ret = openConnection()) < 0)
            return ret;

        return ret;
    }

    int openConnection()
    {
        if ((m_conn = xcb_connect(0, 0)) == 0)
            return xcb_connection_has_error(m_conn);

        return 0;
    }

    void closeConnection()
    {
        xcb_disconnect(m_conn);
    }

private:
    DSTEPWM_DECLARE_PUBLIC(DstepWmXcb)

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

} // namespace wm
} // namespace dstep
