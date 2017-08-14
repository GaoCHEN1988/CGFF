#include "renderer.h"
#include "api/context.h"
#include "platform/opengl/glRenderer.h"

namespace CGFF {

    QSharedPointer<Renderer> Renderer::s_instance = nullptr;

    void Renderer::init()
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::
            OPENGL:	s_instance = nullptr; 
            break;
        case RenderAPI::DIRECT3D:	
            s_instance = nullptr; 
            break;
        }
        s_instance->initInternal();
    }

}