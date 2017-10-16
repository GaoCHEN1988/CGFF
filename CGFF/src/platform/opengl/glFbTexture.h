#ifndef CGFF_GL_FB_TEXTURE_H
#define CGFF_GL_FB_TEXTURE_H

#include "graphic/api/texture2D.h"
#include <QColor>

namespace CGFF {

    class GLFbTexture : public Texture2D
    {
    public:
        GLFbTexture(int width, int height, const TextureParameters& parameters = TextureParameters(), const QString& name = "FramebufferTexture");
     
        virtual ~GLFbTexture();

        void bind(uint slot = 0) override;
        void unBind(uint slot = 0) override;

        inline GLuint getID() const override { return m_glTextureId; }
        inline QString getName() const override { return m_name; }
        inline QString getFilepath() const override { return ""; }
        inline int getWidth() const override { return m_width; }
        inline int getHeight() const override { return m_height; }

        static GLenum toOpenGlPixelFormat(QOpenGLTexture::PixelFormat format);
        static GLuint toOpenGlTextureFormat(QOpenGLTexture::TextureFormat format);
        static GLenum toOpenGlPixelType(QOpenGLTexture::PixelType type);
        static GLenum toOpenGlFilter(QOpenGLTexture::Filter filter);
        static GLenum toOpenGlWrap(QOpenGLTexture::WrapMode wrap);

    private:
        void init();

    private:
        QString m_name;
        int m_width;
        int m_height;
        GLuint m_glTextureId;
        TextureParameters m_textureParams;
    };
}

#endif