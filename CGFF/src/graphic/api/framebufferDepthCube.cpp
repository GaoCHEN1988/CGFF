#include "FramebufferDepthCube.h"
#include "context.h"
#include "platform/opengl/glFramebufferDepthCube.h"

namespace CGFF {

    QSharedPointer<FramebufferDepthCube> FramebufferDepthCube::create(int size)
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:
            return QSharedPointer<GLFramebufferDepthCube>(new GLFramebufferDepthCube(size));
        case RenderAPI::DIRECT3D:
            return nullptr;
        }
        return nullptr;
    }

}