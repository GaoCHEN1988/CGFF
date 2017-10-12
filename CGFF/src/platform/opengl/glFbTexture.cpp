#include "glFbTexture.h"
#include "glContext.h"

namespace CGFF {

    GLFbTexture::GLFbTexture(int width, int height, TextureParameters parameters, const QString& name)
        : m_name(name)
        , m_width(width)
        , m_height(height)
        , m_glTextureId(0)
        , m_textureParams(parameters)
    {
        init();
    }

    GLFbTexture::~GLFbTexture()
    {

    }

    void GLFbTexture::bind(uint slot)
    {
        GL->glActiveTexture(GL_TEXTURE0 + slot);
        GL->glBindTexture(GL_TEXTURE_2D, m_glTextureId);
    }

    void GLFbTexture::unBind(uint slot)
    {
        GL->glActiveTexture(GL_TEXTURE0 + slot);
        GL->glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GLFbTexture::init()
    {
        GL->glGenTextures(1, &m_glTextureId);
        GL->glBindTexture(GL_TEXTURE_2D, m_glTextureId);
        GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
        GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}