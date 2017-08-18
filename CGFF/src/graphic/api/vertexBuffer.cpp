#include "vertexBuffer.h"
#include "context.h"
#include "platform/opengl/glVertexBuffer.h"

namespace CGFF {

    QSharedPointer<VertexBuffer> VertexBuffer::create(BufferUsage usage)
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:
            return QSharedPointer<GLVertexBuffer>(new GLVertexBuffer(usage));
        case RenderAPI::DIRECT3D:
            return nullptr;
        }
		return nullptr;
    }

}