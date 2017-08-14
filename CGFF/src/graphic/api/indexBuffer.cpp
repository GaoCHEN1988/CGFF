#include "indexBuffer.h"
#include "context.h"
#include "platform/opengl/glIndexBuffer.h"

namespace CGFF {

    QSharedPointer<IndexBuffer> IndexBuffer::create(uint* data, uint count)
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:
            return QSharedPointer<GLIndexBuffer>(new GLIndexBuffer(data,count));
        case RenderAPI::DIRECT3D:
            return nullptr;
        }
        return nullptr;
    }

}