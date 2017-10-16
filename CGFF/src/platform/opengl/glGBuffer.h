#ifndef CGFF_GL_GBUFFER_H
#define CGFF_GL_GBUFFER_H

#include "graphic/api/gBuffer.h"
#include "glFbTexture.h"
#include "glTextureDepth.h"

namespace CGFF {

    class GLGBuffer : public GBuffer
    {
    public:
        GLGBuffer(int width, int height);
        ~GLGBuffer();

        void setReadBuffer(TextureType type) override;

        void bind(int mode = 0) override;
        void unBind() override;
        void clear() override;

        void blitDepthBuffer() override;

        int getWidth() const override { return m_width; }
        int getHeight() const override { return m_height; }
        QSize getSize() const override { return QSize(m_width, m_height); }
        QSharedPointer<Texture> getTexture(TextureType type) const
        {
            return m_textures[(uint)type];
        }


    private:
        void init();

    private:
        GLuint m_framebufferHandle;
        GLuint m_depthbufferHandle;

        QSharedPointer<GLFbTexture> m_textures[3];
        int m_width, m_height;
    };

}

#endif