#ifndef RENDERABLE_2D_H
#define RENDERABLE_2D_H

#include "renderer2d.h"
#include "buffer/buffer.h"
#include "buffer/indexBuffer.h"
#include "buffer/vertexArray.h"
#include "../maths/qtmaths.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

namespace CGFF {
	struct VertexData
	{
		QVector3D vertex;
		QVector2D uv;
        QVector2D mask_uv;
		float tid;
        float mid;
		QVector4D color;
	};

	class Renderable2D : public QEnableSharedFromThis<Renderable2D>
	{
	protected:
		Renderable2D() : m_texture(nullptr)
		{
			setDefaultUV();
		}
	public:
		Renderable2D(QVector3D position, QVector2D size, QVector4D color)
			: m_position(position)
			, m_size(size)
			, m_color(color)
			, m_texture(nullptr)
		{
			setDefaultUV();
		}

		virtual ~Renderable2D() 
		{
		}

		virtual void submit(QSharedPointer<Renderer2D> renderer) 
		{
			renderer->submit(sharedFromThis());
		}

	public:

		inline const QVector3D& getPosition() const { return m_position; }
		inline const QVector2D& getSize() const { return m_size; }
		inline const QVector4D& getColor() const { return m_color; }
		inline const std::vector<QVector2D>& getUV() const { return m_UVs; }
        inline const GLuint getTextureID() const { return m_texture == nullptr ? 0 : m_texture->textureId(); }
        inline const QSharedPointer<QOpenGLTexture> getTexture() const { return m_texture; }

	private:
		void setDefaultUV()
		{
			m_UVs.push_back(QVector2D(0, 0));
			m_UVs.push_back(QVector2D(0, 1));
			m_UVs.push_back(QVector2D(1, 1));
			m_UVs.push_back(QVector2D(1, 0));
		}
	protected:
		QVector3D m_position;
		QVector2D m_size;
		QVector4D m_color;
		std::vector<QVector2D> m_UVs;
		QSharedPointer<QOpenGLTexture> m_texture;
	};
}

#endif