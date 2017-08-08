#ifndef TEXTURE_DEPTH_H
#define TEXTURE_DEPTH_H

#include "texture.h"

namespace CGFF {

	class TextureDepth : public QOpenGLTexture
	{
	public:
		TextureDepth(QOpenGLTexture::Target target = TargetCubeMap);

	public:
		static QSharedPointer<TextureDepth> create(uint width, uint height);
	};
}

#endif