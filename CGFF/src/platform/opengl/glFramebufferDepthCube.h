#ifndef CGFF_GL_FRAMEBUFFER_DEPTH_H
#define CGFF_GL_FRAMEBUFFER_DEPTH_H

#include "utils/qtopengl.h"
#include "graphic/api/framebufferDepthCube.h"
#include "glTextureDepthCube.h"

namespace CGFF {

    class GLFramebufferDepthCube : public FramebufferDepthCube
    {
    public:
        GLFramebufferDepthCube(int size);
        ~GLFramebufferDepthCube();

        void bind() override;
        void unBind() override;
        void clear() override;

        int getWidth() const override;
        int getHeight() const override;
        QSize getSize() const override;

        QSharedPointer<Texture> getTexture() const override;
    private:
        void init();

    private:
        GLuint m_framebufferID;
        GLuint m_size;
        QSharedPointer<GLTextureDepthCube> m_glTextureCube;
    };
}

#endif
