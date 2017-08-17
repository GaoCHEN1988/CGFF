#include "sprite.h"

namespace CGFF {

    Sprite::Sprite(QSharedPointer<Texture2D> texture)
        : Renderable2D(QVector3D(0.0f, 0.0f, 0.0f), 
            QVector2D((float)texture->getWidth(), (float)texture->getHeight()), 
            QVector4D(1.0, 1.0, 1.0, 1.0))
        , position(m_position)
        , size(m_size)
    {
        m_texture = texture;
    }
    Sprite::Sprite(float x, float y, QSharedPointer<Texture2D> texture)
        : Renderable2D(QVector3D(x, y, 0.0f),
            QVector2D((float)texture->getWidth(), (float)texture->getHeight()),
            QVector4D(1.0, 1.0, 1.0, 1.0))
        , position(m_position)
        , size(m_size)
    {
        m_texture = texture;
    }

	Sprite::Sprite(float x, float y, float width, float height, QVector4D color)
		: Renderable2D(QVector3D(x, y, 0), QVector2D(width, height), color)
        , position(m_position)
        , size(m_size)
	{
	}

	Sprite::Sprite(float x, float y, float width, float height, QSharedPointer<Texture2D> texture)
		: Renderable2D(QVector3D(x, y, 0), QVector2D(width, height), QVector4D(1,1,1,1))
        , position(m_position)
        , size(m_size)
	{
		m_texture = texture;
	}

    void Sprite::setUV(const QVector<QVector2D>& uv)
    {
        m_UVs = uv;
    }
}