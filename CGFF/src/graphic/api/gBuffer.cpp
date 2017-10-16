#include "gBuffer.h"
#include "context.h"
#include "platform/opengl/glGBuffer.h"

namespace CGFF {

    QSharedPointer<GBuffer> GBuffer::create(int width, int height)
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:
            return QSharedPointer<GLGBuffer>(new GLGBuffer(width, height));
        case RenderAPI::DIRECT3D:
            return nullptr;
        }
        return nullptr;
    }
}