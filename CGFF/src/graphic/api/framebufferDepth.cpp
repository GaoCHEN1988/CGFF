#include "framebufferDepth.h"
#include "context.h"
#include "platform/opengl/glFramebufferDepth.h"

namespace CGFF {

	QSharedPointer<FramebufferDepth> FramebufferDepth::create(int width, int height)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
            return QSharedPointer<GLFramebufferDepth>(new GLFramebufferDepth(width, height));
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
		return nullptr;
	}

}
