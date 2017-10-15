#include "glGBuffer.h"
#include "utils/qtopengl.h"

namespace CGFF {

    GLGBuffer::GLGBuffer(int width, int height)
        : m_framebufferHandle(0)
        , m_depthbufferHandle(0)
        , m_width(width)
        , m_height(height)
    {
        init();
    }

    GLGBuffer::~GLGBuffer()
    {
        GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
        for (int i = 0; i < 3; i++)
        {
            m_textures[i].clear();
        }
    }

    void GLGBuffer::setReadBuffer(TextureType type)
    {
        GL->glReadBuffer(GL_COLOR_ATTACHMENT0 + (uint)type);
        GL->glBlitFramebuffer(0, 0, m_width, m_height,
            0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    }

    void GLGBuffer::bind(int mode)
    {
        GL->glDisable(GL_BLEND);

        GL->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle);
    }

    void GLGBuffer::unBind()
    {
        GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);

        GL->glEnable(GL_BLEND);
    }

    void GLGBuffer::clear() 
    {
        GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLGBuffer::blitDepthBuffer()
    {
        GL->glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebufferHandle);
        GL->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        GL->glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GLGBuffer::init()
    {
        // configure g-buffer framebuffer
        // ------------------------------
        GL->glGenFramebuffers(1, &m_framebufferHandle);
        GL->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle);

        GLTextureParameters param;
        param.InternalFormat = GL_RGB32F;
        param.Format = GL_RGB;
        param.Type = GL_FLOAT;
        param.MinTexParameter = GL_NEAREST;
        param.MaxTexParameter = GL_NEAREST;

        //param.InternalFormat = GL_RGBA;
        //param.Format = GL_RGBA;
        //param.Type = GL_UNSIGNED_BYTE;
        //param.MinTexParameter = GL_NEAREST;
        //param.MaxTexParameter = GL_NEAREST;

        m_textures[0] = QSharedPointer<GLFbTexture>(new GLFbTexture(m_width, m_height, param));
        GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textures[0]->getID(), 0);

        // normal color buffer
        m_textures[1] = QSharedPointer<GLFbTexture>(new GLFbTexture(m_width, m_height, param));
        GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textures[1]->getID(), 0);

        // color + specular color buffer
        param.InternalFormat = GL_RGBA;
        param.Format = GL_RGBA;
        param.Type = GL_UNSIGNED_BYTE;
        param.MinTexParameter = GL_NEAREST;
        param.MaxTexParameter = GL_NEAREST;
        m_textures[2] = QSharedPointer<GLFbTexture>(new GLFbTexture(m_width, m_height, param));
        GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_textures[2]->getID(), 0);

        // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        GL->glDrawBuffers(3, attachments);

        // create and attach depth buffer (renderbuffer)
        GL->glGenRenderbuffers(1, &m_depthbufferHandle);
        GL->glBindRenderbuffer(GL_RENDERBUFFER, m_depthbufferHandle);
        GL->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
        GL->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbufferHandle);
        // finally check if framebuffer is complete
        Q_ASSERT(GL->glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

        GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}