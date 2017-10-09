#ifndef CGFF_TEXTURE_DEPTH_CUBE_H
#define CGFF_TEXTURE_DEPTH_CUBE_H

#include "texture.h"

namespace CGFF {

    class TextureDepthCube : public Texture
    {
    public:
        static QSharedPointer<TextureDepthCube> create(int size);
    };
}

#endif