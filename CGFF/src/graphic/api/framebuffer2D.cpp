#include "framebuffer2D.h"
#include "context.h"
#include "platform/opengl/glFramebuffer2D.h"

namespace CGFF {

	QSharedPointer<Framebuffer2D> Framebuffer2D::create(int width, int height)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:	
			return QSharedPointer<GLFramebuffer2D>(new GLFramebuffer2D(width, height));
		case RenderAPI::DIRECT3D:	
			return nullptr;
		}
		return nullptr;
	}

}