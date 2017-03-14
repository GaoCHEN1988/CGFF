#ifndef RENDERABLE_2D_H
#define RENDERABLE_2D_H

#include "buffer/buffer.h"
#include "buffer/indexBuffer.h"
#include "buffer/vertexArray.h"
#include "../maths/qtmaths.h"
#include <QOpenGLShaderProgram>

namespace CGFF {
	struct VertexData
	{
		QVector3D vertex;
		QVector4D color;
	};

	class Renderable2D
	{
	public:
		Renderable2D(QVector3D position, QVector2D size, QVector4D color)
			: m_position(position)
			, m_size(size)
			, m_color(color)
		{
		}

		virtual ~Renderable2D() 
		{
		}

	public:

		inline const QVector3D& getPosition() const { return m_position; }
		inline const QVector2D& getSize() const { return m_size; }
		inline const QVector4D& getColor() const { return m_color; }

	protected:
		QVector3D m_position;
		QVector2D m_size;
		QVector4D m_color;

	};
}

#endif