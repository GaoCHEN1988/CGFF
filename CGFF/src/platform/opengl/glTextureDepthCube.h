#ifndef CGFF_GL_TEXTURE_DEPTH_CUBE_H
#define CGFF_GL_TEXTURE_DEPTH_CUBE_H

#include "graphic/api/textureDepthCube.h"

namespace CGFF {

    class GLTextureDepthCube : public TextureDepthCube
    {
    public:
        GLTextureDepthCube(int size);
        virtual ~GLTextureDepthCube() {};

        void bind(uint slot = 0) override;
        void unBind(uint slot = 0) override;

        inline GLuint getID() const { return m_handle; }
        inline QString getName() const override { return m_name; }
        inline QString getFilepath() const override { return m_fileName; }
        inline int getWidth() const override { return m_size; }
        inline int getHeight() const override { return m_size; }

    private:
        void init();

    private:
        QString m_name;
        QString m_fileName;
        int m_size;
        GLuint m_handle;
    };

}

#endif