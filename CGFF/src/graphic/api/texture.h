#ifndef CGFF_TEXTURE_H
#define CGFF_TEXTURE_H

#include "utils/types.h"
#include <QOpenGLTexture>

namespace CGFF {

    struct TextureParameters
    {
		//Paramters for opengl
		QOpenGLTexture::PixelFormat gl_pixelFormat;
		QOpenGLTexture::TextureFormat gl_textureFormat;
		QImage::Format imageFormat;
		QOpenGLTexture::PixelType gl_pixelType;
        QOpenGLTexture::Filter gl_filter;
        QOpenGLTexture::WrapMode gl_wrap;

		//To implement: parameters for directX
		//to do

        TextureParameters()
        {
			gl_pixelFormat = QOpenGLTexture::PixelFormat::RGBA;
			gl_textureFormat = QOpenGLTexture::RGBA8_UNorm;
			imageFormat = QImage::Format_RGBA8888;
			gl_pixelType = QOpenGLTexture::UInt8;
            gl_filter = QOpenGLTexture::Filter::Linear;
            gl_wrap = QOpenGLTexture::WrapMode::ClampToEdge;
        }

        TextureParameters(QOpenGLTexture::PixelFormat gl_pixelFormat
			, QOpenGLTexture::TextureFormat gl_textureFormat
			, QImage::Format imageFormat
			, QOpenGLTexture::PixelType gl_pixelType
			, QOpenGLTexture::Filter gl_filter
			, QOpenGLTexture::WrapMode gl_wrap)
            : gl_pixelFormat(gl_pixelFormat)
			, gl_textureFormat(gl_textureFormat)
			, imageFormat(imageFormat)
			, gl_pixelType(gl_pixelType)
            , gl_filter(gl_filter)
            , gl_wrap(gl_wrap)
        {
        }

        TextureParameters(QOpenGLTexture::Filter gl_filter)
            : gl_pixelFormat(QOpenGLTexture::PixelFormat::RGBA)
			, gl_textureFormat(QOpenGLTexture::RGBA8_UNorm)
			, imageFormat(QImage::Format_RGBA8888)
			, gl_pixelType(QOpenGLTexture::UInt8)
            , gl_filter(gl_filter)
            , gl_wrap(QOpenGLTexture::WrapMode::ClampToEdge)
        {
        }

        TextureParameters(QOpenGLTexture::Filter gl_filter, QOpenGLTexture::WrapMode gl_wrap)
            : gl_pixelFormat(QOpenGLTexture::PixelFormat::RGBA)
			, gl_textureFormat(QOpenGLTexture::RGBA8_UNorm)
			, imageFormat(QImage::Format_RGBA8888)
			, gl_pixelType(QOpenGLTexture::UInt8)
            , gl_filter(gl_filter)
			, gl_wrap(gl_wrap)
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

	class Texture
	{
	public:
		virtual void bind(uint slot = 0) = 0;
		virtual void unBind(uint slot = 0) = 0;

		virtual QString getName() const = 0;
		virtual QString getFilepath() const = 0;
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

	};


}

#endif