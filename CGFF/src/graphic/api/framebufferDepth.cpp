#include "framebufferDepth.h"
#include "context.h"

namespace CGFF {

	QSharedPointer<FramebufferDepth> FramebufferDepth::create(int width, int height)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return nullptr;
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
		return nullptr;
	}

}
