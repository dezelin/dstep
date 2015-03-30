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

#ifndef COLORMAP_H
#define COLORMAP_H

#include "object.h"

#include <QColor>
#include <QObject>
#include <QtPlugin>

namespace dstep
{
namespace wm
{
namespace interfaces
{

class Colormap : public Object
{
public:
    typedef enum Mode { Direct, Indexed, Gray } Mode;

    virtual ~Colormap()
    {
    }

    virtual int init() = 0;

    virtual QColor colorAt(uint pixel) const = 0;
    virtual const QVector<QColor> &colormap() const = 0;
    virtual int depth() const = 0;
    virtual Mode mode() const = 0;
    virtual uint pixel(const QColor &color) const = 0;
    virtual int size() const = 0;
};

} // namespace interfaces
} // namespace wm
} // namespace dstep

#define Colormap_iid "org.dstep.wm.interfaces.Colormap/1.0"
Q_DECLARE_INTERFACE(dstep::wm::interfaces::Colormap, Colormap_iid)

#endif // COLORMAP_H
