#ifndef SPRITE_H
#define SPRITE_H

#include "renderable2d.h"

namespace CGFF {

	class Sprite : public Renderable2D
	{
	public:
		Sprite(float x, float y, float width, float height, QVector4D color);
		Sprite(float x, float y, float width, float height, QSharedPointer<QOpenGLTexture> texture);
		~Sprite() {	};
	};
}

#endif