#include "context.h"
#include "platform/opengl/glContext.h"

namespace CGFF {

	QSharedPointer<Context> Context::s_context = nullptr;
    RenderAPI Context::s_renderAPI = RenderAPI::NONE;

    Context::~Context()
    {
    }

	void Context::create(QWindow *parent)
	{
		switch (getRenderAPI())
		{
		case RenderAPI::OPENGL:		
			s_context = QSharedPointer<GLContext>(new GLContext(parent));
			break;
		case RenderAPI::DIRECT3D:	
			s_context = nullptr; 
			break;
		}
	}

}