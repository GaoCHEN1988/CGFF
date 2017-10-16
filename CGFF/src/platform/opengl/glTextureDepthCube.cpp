#include "glTextureDepthCube.h"
#include "utils/qtopengl.h"

namespace CGFF {

    GLTextureDepthCube::GLTextureDepthCube(int size)
        : m_size(size)
        , m_handle(0)
    {
        init();
    }

    void GLTextureDepthCube::bind(uint slot)
    {
        GL->glActiveTexture(GL_TEXTURE0 + slot);
        GL->glBindTexture(GL_TEXTURE_2D, m_handle);
    }

    void GLTextureDepthCube::unBind(uint slot) 
    {
        GL->glActiveTexture(GL_TEXTURE0 + slot);
        GL->glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GLTextureDepthCube::init()
    {
        GL->glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);

        for (unsigned int i = 0; i < 6; ++i)
            GL->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_size, m_size, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

        GL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        GL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        GL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        GL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        GL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
}