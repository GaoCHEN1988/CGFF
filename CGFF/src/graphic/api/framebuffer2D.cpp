#include "framebuffer2D.h"
#include "context.h"

namespace CGFF {

	QSharedPointer<Framebuffer2D> Framebuffer2D::create(int width, int height)
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