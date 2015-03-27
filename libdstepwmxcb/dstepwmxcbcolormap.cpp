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

#include "dstepwmxcbcolormap.h"

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbColormap::DstepWmXcbColormapPrivate
{
public:
    DstepWmXcbColormapPrivate(DstepWmXcbColormap *parent) :
        q_ptr(parent)
    {

    }

    const QColor &colorAt(uint pixel) const
    {
    }

    const QVector<QColor> &colormap() const
    {

    }

    int depth() const
    {

    }

    Colormap::Mode mode() const
    {

    }

    uint pixel(const QColor &color) const
    {

    }

    int size() const
    {

    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbColormap)
};

DstepWmXcbColormap::DstepWmXcbColormap(QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbColormapPrivate(this))
{
}

const QColor &DstepWmXcbColormap::colorAt(uint pixel) const
{
    Q_D(const DstepWmXcbColormap);
    return d->colorAt(pixel);
}

const QVector<QColor> &DstepWmXcbColormap::colormap() const
{
    Q_D(const DstepWmXcbColormap);
    return d->colormap();
}

int DstepWmXcbColormap::depth() const
{
    Q_D(const DstepWmXcbColormap);
    return d->depth();
}

Colormap::Mode DstepWmXcbColormap::mode() const
{
    Q_D(const DstepWmXcbColormap);
    return d->mode();
}

uint DstepWmXcbColormap::pixel(const QColor &color) const
{
    Q_D(const DstepWmXcbColormap);
    return d->pixel(color);
}

int DstepWmXcbColormap::size() const
{
    Q_D(const DstepWmXcbColormap);
    return d->size();
}

} // namespace wm
} // namespace dstep
