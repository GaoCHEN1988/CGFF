#include "staticSprite.h"

namespace CGFF {

	StaticSprite::StaticSprite(float x, float y, float width, float height, QVector4D color, QOpenGLShaderProgram& shader)
		: Renderable2D(QVector3D(x, y, 0), QVector2D(width, height), color)
		, m_shaderProgram(shader)
		, m_verticesLocation(0)
		, m_colorsLocation(1)
	{
		GLfloat vertices[] =
		{
			x, y, 0,
			x + width, y, 0,
			x + width, y+ height, 0,
			x, y + height, 0
		};

		GLfloat colors[] =
		{
			color.x(), color.y(), color.z(), color.w(),
			color.x(), color.y(), color.z(), color.w(),
			color.x(), color.y(), color.z(), color.w(),
			color.x(), color.y(), color.z(), color.w()
		};

		m_vertexarray = new VertexArray();

		m_vertexarray->addBuffer(new CGFF::Buffer(vertices, 4 * 3, 3), m_verticesLocation);
		m_vertexarray->addBuffer(new CGFF::Buffer(colors, 4 * 4, 4), m_colorsLocation);

		GLuint indices[] = {0,1,2,2,3,0};
		m_indexBuffer = new IndexBuffer(indices, 6);

	}

	StaticSprite::~StaticSprite()
	{
		if (m_vertexarray)
			delete m_vertexarray;

		if (m_indexBuffer)
			delete m_indexBuffer;
	}

}