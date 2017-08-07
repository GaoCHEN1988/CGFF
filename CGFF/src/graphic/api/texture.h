#ifndef CGFF_TEXTURE_H
#define CGFF_TEXTURE_H

#include "utils/types.h"
#include <QOpenGLTexture>

namespace CGFF {

    struct TextureParameters
    {
        QOpenGLTexture::PixelFormat format;
        QOpenGLTexture::Filter filter;
        QOpenGLTexture::WrapMode wrap;

        TextureParameters()
        {
            format = QOpenGLTexture::PixelFormat::RGBA;
            filter = QOpenGLTexture::Filter::Linear;
            wrap = QOpenGLTexture::WrapMode::ClampToEdge;
        }

        TextureParameters(QOpenGLTexture::PixelFormat format, QOpenGLTexture::Filter filter, QOpenGLTexture::WrapMode wrap)
            : format(format)
            , filter(filter)
            , wrap(wrap)
        {
        }

        TextureParameters(QOpenGLTexture::Filter filter)
            : format(QOpenGLTexture::PixelFormat::RGBA)
            , filter(filter)
            , wrap(QOpenGLTexture::WrapMode::ClampToEdge)
        {
        }

        TextureParameters(QOpenGLTexture::Filter filter, QOpenGLTexture::WrapMode wrap)
            : format(QOpenGLTexture::PixelFormat::RGBA)
            , filter(filter), wrap(wrap)
        {
        }
    };

    struct TextureLoadOptions
    {
        bool flipX;
        bool flipY;

        TextureLoadOptions()
        {
            flipX = false;
            flipY = false;
        }

        TextureLoadOptions(bool flipX, bool flipY)
            : flipX(flipX), flipY(flipY)
        {
        }
    };

}

#endif