#include "vertexBuffer.h"
#include "context.h"

namespace CGFF {

    QSharedPointer<VertexBuffer> VertexBuffer::create(BufferUsage usage = BufferUsage::STATIC)
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:
            return nullptr;
        case RenderAPI::DIRECT3D:
            return nullptr;
        }
    }

}