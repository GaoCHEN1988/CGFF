#ifndef TEXTURE_DEPTH_H
#define TEXTURE_DEPTH_H

#include "texture.h"

namespace CGFF {

	class TextureDepth : public Texture
	{
	public:
		static QSharedPointer<TextureDepth> create(int width, int height);
	};
}

#endif