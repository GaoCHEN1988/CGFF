#include "batchRenderer2d.h"

namespace CGFF {

	BatchRenderer2D::BatchRenderer2D() 
		: Renderer2D()
		, m_indexCount(0)
	{
		initializeOpenGLFunctions();
		
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void BatchRenderer2D::init()
	{
		glGenVertexArrays(1, &m_VAO);	
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)0);
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)(3*sizeof(GLfloat)));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
		//GLuint indices[RENDERER_INDICES_SIZE];
		int offset = 0;

		for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}
		m_IBO = QSharedPointer<CGFF::IndexBuffer>(new CGFF::IndexBuffer(indices, RENDERER_INDICES_SIZE));
	
		glBindVertexArray(0);

		delete[] indices;

		m_indexCount = 0;
	}

	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	void BatchRenderer2D::submit(QSharedPointer<Renderable2D> renderable)
	{
		const QVector3D& position = renderable->getPosition();
		const QVector2D& size = renderable->getSize();
		const QVector4D& color = renderable->getColor();

		m_buffer->vertex = position;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = QVector3D(position.x(), position.y() + size.y(), position.z());
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = QVector3D(position.x() + size.x(), position.y() + size.y(), position.z());
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = QVector3D(position.x() + size.x(), position.y(), position.z());
		m_buffer->color = color;
		m_buffer++;

		m_indexCount += 6;
	}

	void BatchRenderer2D::flush() 
	{
		glBindVertexArray(m_VAO);
		m_IBO->bind();

		GLenum error = glGetError();
		
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);
		error = glGetError();
		m_IBO->unbind();
		glBindVertexArray(0);

		m_indexCount = 0;
	}
	void BatchRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}