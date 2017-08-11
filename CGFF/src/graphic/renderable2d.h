#ifndef CGFF_RENDERABLE_2D_H
#define CGFF_RENDERABLE_2D_H

#include "renderer2d.h"
#include "../utils/qtopengl.h"
#include "../maths/qtmaths.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

namespace CGFF {

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
		inline const QVector<QVector2D>& getUV() const { return m_UVs; }
        inline const GLuint getTextureID() const { return m_texture == nullptr ? 0 : m_texture->textureId(); }
        inline const QSharedPointer<QOpenGLTexture> getTexture() const { return m_texture; }
        inline bool isVisible() const { return m_isVisible; }
        inline void setVisible(bool visible) { m_isVisible = visible; }

        static QVector<QVector2D> getDefaultUVs()
        {
            static QVector<QVector2D> results;
            if (!results.size())
            {
                results.push_back(QVector2D(0, 0));
                results.push_back(QVector2D(0, 1));
                results.push_back(QVector2D(1, 1));
                results.push_back(QVector2D(1, 0));
            }
            return results;
        }

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
		QVector<QVector2D> m_UVs;
		QSharedPointer<QOpenGLTexture> m_texture;
        bool m_isVisible;
	};
}

#endif