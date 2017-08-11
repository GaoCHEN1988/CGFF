#ifndef CGFF_SPRITE_H
#define CGFF_SPRITE_H

#include "renderable2d.h"

namespace CGFF {

	class Sprite : public Renderable2D
	{
	public:
        explicit Sprite(QSharedPointer<QOpenGLTexture> texture);
        Sprite(float x, float y, QSharedPointer<QOpenGLTexture> texture);
		Sprite(float x, float y, float width, float height, QVector4D color);
		Sprite(float x, float y, float width, float height, QSharedPointer<QOpenGLTexture> texture);
		~Sprite() {	};

        void setUV(const QVector<QVector2D>& uv);

    public:
        QVector3D& position;
        QVector2D& size;
	};
}

#endif