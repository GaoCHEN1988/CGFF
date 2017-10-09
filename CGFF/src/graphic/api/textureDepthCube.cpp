#include "textureDepthCube.h"
#include "context.h"
#include "platform/opengl/glTextureDepthCube.h"

namespace CGFF {


    QSharedPointer<TextureDepthCube> TextureDepthCube::create(int size)
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:
            return QSharedPointer<TextureDepthCube>(new GLTextureDepthCube(size));
        case RenderAPI::DIRECT3D:
            return nullptr;
        }
        return nullptr;
    }

}