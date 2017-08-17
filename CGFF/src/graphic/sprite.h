#ifndef CGFF_SPRITE_H
#define CGFF_SPRITE_H

#include "renderable2d.h"

namespace CGFF {

	class Sprite : public Renderable2D
	{
	public:
        explicit Sprite(QSharedPointer<Texture2D> texture);
        Sprite(float x, float y, QSharedPointer<Texture2D> texture);
		Sprite(float x, float y, float width, float height, QVector4D color);
		Sprite(float x, float y, float width, float height, QSharedPointer<Texture2D> texture);
		~Sprite() {	};

        void setUV(const QVector<QVector2D>& uv);
		inline void SetTexture(QSharedPointer<Texture2D> texture) { m_texture = texture; }

    public:
        QVector3D& position;
        QVector2D& size;
	};
}

#endif