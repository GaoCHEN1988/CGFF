#ifndef CGFF_TEXTURE_H
#define CGFF_TEXTURE_H

#include "utils/types.h"
#include <QOpenGLTexture>

namespace CGFF {

    struct TextureParameters
    {
		QOpenGLTexture::PixelFormat pixelFormat;
		QOpenGLTexture::TextureFormat textureFormat;
		QImage::Format imageFormat;
		QOpenGLTexture::PixelType pixelType;
        QOpenGLTexture::Filter filter;
        QOpenGLTexture::WrapMode wrap;

        TextureParameters()
        {
			pixelFormat = QOpenGLTexture::PixelFormat::RGBA;
			textureFormat = QOpenGLTexture::RGBA8_UNorm;
			imageFormat = QImage::Format_RGBA8888;
			pixelType = QOpenGLTexture::UInt8;
            filter = QOpenGLTexture::Filter::Linear;
            wrap = QOpenGLTexture::WrapMode::ClampToEdge;
        }

        TextureParameters(QOpenGLTexture::PixelFormat pixelFormat
			, QOpenGLTexture::TextureFormat textureFormat
			, QImage::Format imageFormat
			, QOpenGLTexture::PixelType pixelType
			, QOpenGLTexture::Filter filter
			, QOpenGLTexture::WrapMode wrap)
            : pixelFormat(pixelFormat)
			, textureFormat(textureFormat)
			, imageFormat(imageFormat)
			, pixelType(pixelType)
            , filter(filter)
            , wrap(wrap)
        {
        }

        TextureParameters(QOpenGLTexture::Filter filter)
            : pixelFormat(QOpenGLTexture::PixelFormat::RGBA)
			, textureFormat(QOpenGLTexture::RGBA8_UNorm)
			, imageFormat(QImage::Format_RGBA8888)
			, pixelType(QOpenGLTexture::UInt8)
            , filter(filter)
            , wrap(QOpenGLTexture::WrapMode::ClampToEdge)
        {
        }

        TextureParameters(QOpenGLTexture::Filter filter, QOpenGLTexture::WrapMode wrap)
            : pixelFormat(QOpenGLTexture::PixelFormat::RGBA)
			, textureFormat(QOpenGLTexture::RGBA8_UNorm)
			, imageFormat(QImage::Format_RGBA8888)
			, pixelType(QOpenGLTexture::UInt8)
            , filter(filter)
			, wrap(wrap)
        {
        }
    };

    struct TextureLoadOptions
    {
        bool horizontalFlip;
        bool verticalFlip;

        TextureLoadOptions()
        {
			horizontalFlip = false;
			verticalFlip = true;
        }

        TextureLoadOptions(bool horizontal, bool vertical)
            : horizontalFlip(horizontal), verticalFlip(vertical)
        {
        }
    };

}

#endif