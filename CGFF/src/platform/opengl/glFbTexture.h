#ifndef CGFF_GL_FB_TEXTURE_H
#define CGFF_GL_FB_TEXTURE_H

#include "graphic/api/texture2D.h"
#include <QColor>

namespace CGFF {

    struct GLTextureParameters
    {
        GLuint InternalFormat;
        GLenum Format;
        GLenum Type;
        GLenum MinTexParameter;
        GLenum MaxTexParameter;

        GLTextureParameters()
            : InternalFormat(GL_RGBA16F)
            , Format(GL_RGBA)
            , Type(GL_FLOAT)
            , MinTexParameter(GL_LINEAR)
            , MaxTexParameter(GL_LINEAR)
        {
        }
    };

    class GLFbTexture : public Texture2D
    {
    public:
        GLFbTexture(int width, int height, GLTextureParameters parameters = GLTextureParameters(), const QString& name = "FramebufferTexture");
     
        virtual ~GLFbTexture();

        void bind(uint slot = 0) override;
        void unBind(uint slot = 0) override;

        inline GLuint getID() const override { return m_glTextureId; }
        inline QString getName() const override { return m_name; }
        inline QString getFilepath() const override { return ""; }
        inline int getWidth() const override { return m_width; }
        inline int getHeight() const override { return m_height; }

    private:
        void init();

    private:
        QString m_name;
        int m_width;
        int m_height;
        GLuint m_glTextureId;
        GLTextureParameters m_textureParams;
    };
}

#endif