#include "sprite.h"

namespace CGFF {

	Sprite::Sprite(float x, float y, float width, float height, QVector4D color)
		: Renderable2D(QVector3D(x, y, 0), QVector2D(width, height), color)
	{
	}

	Sprite::Sprite(float x, float y, float width, float height, QSharedPointer<QOpenGLTexture> texture)
		: Renderable2D(QVector3D(x, y, 0), QVector2D(width, height), QVector4D(1,1,1,1))
	{
		m_texture = texture;
	}

}