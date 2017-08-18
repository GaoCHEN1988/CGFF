#include "vertexArray.h"
#include "platform/opengl/glVertexArray.h"

namespace CGFF {

    QSharedPointer<VertexArray> VertexArray::create()
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:
            return QSharedPointer<GLVertexArray>(new GLVertexArray);
        case RenderAPI::DIRECT3D:
            return nullptr;
        }
		return nullptr;
    }

}