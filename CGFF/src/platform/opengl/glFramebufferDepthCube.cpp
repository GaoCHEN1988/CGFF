#include "glFramebufferDepthCube.h"

namespace CGFF {

    GLFramebufferDepthCube::GLFramebufferDepthCube(int size)
        : m_size(size)
    {
        init();
    }

    GLFramebufferDepthCube::~GLFramebufferDepthCube()
    {
        GL->glDeleteFramebuffers(1, &m_framebufferID);
    }

    void GLFramebufferDepthCube::bind()
    {
        GL->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
    }

    void GLFramebufferDepthCube::unBind()
    {
        GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GLFramebufferDepthCube::clear()
    {
        GL->glClear(GL_DEPTH_BUFFER_BIT);
    }

    int GLFramebufferDepthCube::getWidth() const
    {
        return m_size;
    }

    int GLFramebufferDepthCube::getHeight() const
    {
        return m_size;
    }

    QSize GLFramebufferDepthCube::getSize() const
    {
        return QSize(m_size, m_size);
    }

    QSharedPointer<Texture> GLFramebufferDepthCube::getTexture() const
    {
        return m_glTextureCube;
    }

    void GLFramebufferDepthCube::init()
    {
        m_glTextureCube = QSharedPointer<GLTextureDepthCube>(new GLTextureDepthCube(m_size));

        GLCall(GL->glGenFramebuffers(1, &m_framebufferID));
        GLCall(GL->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID));

        GLCall(GL->glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_glTextureCube->getID(), 0));
        GLCall(GL->glDrawBuffer(GL_NONE));
        GLCall(GL->glReadBuffer(GL_NONE));
        //GLenum test = GL->glCheckFramebufferStatus(GL_FRAMEBUFFER);
        //Q_ASSERT(GL->glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

        GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}