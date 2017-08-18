#include "textureDepth.h"
#include "context.h"
#include "platform/opengl/glTextureDepth.h"

namespace CGFF {


	QSharedPointer<TextureDepth> TextureDepth::create(int width, int height)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return QSharedPointer<TextureDepth>(new GLTextureDepth(width, height));
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
		return nullptr;
	}

}