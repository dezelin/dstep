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

#include <QDebug>
#include <QVector>

#ifndef QT_QWS_DEPTH16_RGB
    #define QT_QWS_DEPTH16_RGB 565
#endif

namespace dstep
{
namespace wm
{

using namespace dstep::wm::interfaces;

class DstepWmXcbColormap::DstepWmXcbColormapPrivate
{
public:
    DstepWmXcbColormapPrivate(DstepWmXcbColormap *parent,
        const xcb_visualtype_t *visual, int depth) :
        q_ptr(parent), m_mode(Colormap::Direct), m_depth(depth), m_size(-1),
            m_bitsPerRgb(0), m_redMask(0), m_greenMask(0), m_blueMask(0),
            m_visual(visual)
    {
        Q_ASSERT(parent);
        Q_ASSERT(visual);
    }

    int init()
    {
        Q_ASSERT(m_visual);
        if (!m_visual)
            return -1;

        int err;
        if ((err = initVisual(m_visual)) < 0) {
            qDebug() << "Error initializing colormap for visual, err:" << err;
            return err;
        }

        return err;
    }

    QColor colorAt(uint pixel) const
    {
        QColor color;
        if (m_mode == Colormap::Direct) {
            if (m_depth == 16)
                pixel = qt_conv16ToRgb(pixel);

            // TODO: Fix this to work with provided XCB visual
            const int red_shift = 16;
            const int green_shift = 8;
            const int red_mask   = 0xff0000;
            const int green_mask = 0x00ff00;
            const int blue_mask  = 0x0000ff;
            color = QColor((pixel & red_mask) >> red_shift,
                           (pixel & green_mask) >> green_shift,
                           (pixel & blue_mask));
        }

        return color;
    }

    const QVector<QColor> &colormap() const
    {
        return m_colormap;
    }

    int depth() const
    {
        return m_depth;
    }

    Colormap::Mode mode() const
    {
        return m_mode;
    }

    uint pixel(const QColor &color) const
    {
        uint ret = 0;
        QRgb rgb = color.rgba();
        if (m_mode == Colormap::Direct) {
            switch(m_depth) {
                case 16: {
                    ret = qt_convRgbTo16(rgb);
                    break;
                }
                case 24:
                case 32: {
                    const int r = qRed(rgb);
                    const int g = qGreen(rgb);
                    const int b = qBlue(rgb);
                    const int red_shift = 16;
                    const int green_shift = 8;
                    const int red_mask   = 0xff0000;
                    const int green_mask = 0x00ff00;
                    const int blue_mask  = 0x0000ff;
                    const int tg = g << green_shift;
                    const int tr = r << red_shift;
                    ret = 0xff000000 | (b & blue_mask) | (tg & green_mask) | (tr & red_mask);
                    break;
                }
                default: {
                    // Should not be there
                    Q_ASSERT(!"Unsupported color depth.");
                    qDebug() << "Unsupported color depth.";
                    break;
                }
            }
        }

        return ret;
    }

    int size() const
    {
        return m_size;
    }

private:
    static const int qt_rbits = (QT_QWS_DEPTH16_RGB / 100);
    static const int qt_gbits = (QT_QWS_DEPTH16_RGB / 10 % 10);
    static const int qt_bbits = (QT_QWS_DEPTH16_RGB % 10);
    static const int qt_red_shift = qt_bbits + qt_gbits - (8 - qt_rbits);
    static const int qt_green_shift = qt_bbits - (8 - qt_gbits);
    static const int qt_neg_blue_shift = 8 - qt_bbits;
    static const int qt_red_rounding_shift = qt_red_shift + qt_rbits;
    static const int qt_green_rounding_shift = qt_green_shift + qt_gbits;
    static const int qt_blue_rounding_shift = qt_bbits - qt_neg_blue_shift;

    ushort qt_convRgbTo16(QRgb c) const
    {
        const int tr = qRed(c) << qt_red_shift;
        const int tg = qGreen(c) << qt_green_shift;
        const int tb = qBlue(c) >> qt_neg_blue_shift;

        return (tb & m_blueMask) | (tg & m_greenMask) | (tr & m_redMask);
    }

    QRgb qt_conv16ToRgb(ushort c) const
    {
        const int r = (c & m_redMask);
        const int g = (c & m_greenMask);
        const int b = (c & m_blueMask);
        const int tr = r >> qt_red_shift | r >> qt_red_rounding_shift;
        const int tg = g >> qt_green_shift | g >> qt_green_rounding_shift;
        const int tb = b << qt_neg_blue_shift | b >> qt_blue_rounding_shift;

        return qRgb(tr,tg,tb);
    }

    int initVisual(const xcb_visualtype_t *visual)
    {
        Q_ASSERT(visual);
        m_bitsPerRgb = visual->bits_per_rgb_value;
        // TODO: Fix to support grayscale screens
        m_mode = m_depth > 8 ? Colormap::Direct : Colormap::Indexed;
        m_size = visual->colormap_entries;
        m_redMask = visual->red_mask;
        m_greenMask = visual->green_mask;
        m_blueMask = visual->blue_mask;

        return 0;
    }

private:
    DSTEP_DECLARE_PUBLIC(DstepWmXcbColormap)

    QVector<QColor> m_colormap;
    Colormap::Mode m_mode;
    int m_depth;
    int m_size;
    int m_bitsPerRgb;
    uint m_redMask, m_greenMask, m_blueMask;

    const xcb_visualtype_t *m_visual;
};

DstepWmXcbColormap::DstepWmXcbColormap(const xcb_visualtype_t *visual, int depth,
    QObject *parent) :
    QObject(parent), d_ptr(new DstepWmXcbColormapPrivate(this, visual, depth))
{
}

int DstepWmXcbColormap::init()
{
    Q_D(DstepWmXcbColormap);
    return d->init();
}

QColor DstepWmXcbColormap::colorAt(uint pixel) const
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
