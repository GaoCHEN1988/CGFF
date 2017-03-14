#ifndef STATIC_SPRITE_H
#define STATIC_SPRITE_H

#include "renderable2d.h"

namespace CGFF {

	class StaticSprite : public Renderable2D
	{
	public:
		StaticSprite(float x, float y, float width, float height, QVector4D color, QOpenGLShaderProgram& shader);
		~StaticSprite();

		inline VertexArray* getVAO() const { return m_vertexarray; }
		inline IndexBuffer* getIBO() const { return m_indexBuffer; }
		inline QOpenGLShaderProgram& getShader() const { return m_shaderProgram; }

	private:
		VertexArray * m_vertexarray;
		IndexBuffer * m_indexBuffer;

		QOpenGLShaderProgram& m_shaderProgram;

		GLuint m_verticesLocation;
		GLuint m_colorsLocation;

	};
	
}

#endif