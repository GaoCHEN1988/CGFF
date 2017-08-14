#include "vertexArray.h"

namespace CGFF {

    QSharedPointer<VertexArray> VertexArray::create()
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