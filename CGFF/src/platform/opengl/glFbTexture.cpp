#include "glFbTexture.h"
#include "glContext.h"

namespace CGFF {

    GLFbTexture::GLFbTexture(int width, int height, GLTextureParameters parameters, const QString& name)
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
        GL->glBindTexture(GL_TEXTURE_2D, 0);
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
        GL->glTexImage2D(GL_TEXTURE_2D, 0, m_textureParams.InternalFormat, m_width, m_height, 0, m_textureParams.Format, m_textureParams.Type, NULL);
        GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_textureParams.MinTexParameter);
        GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_textureParams.MaxTexParameter);
    }
}