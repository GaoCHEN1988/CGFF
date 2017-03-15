#include "vertexArray.h"

namespace CGFF {

	VertexArray::VertexArray()
	{
		initializeOpenGLFunctions();
		glGenVertexArrays(1, &m_arrayID);
	}

	VertexArray::~VertexArray() 
	{
		for (int i = 0; i < m_buffers.size(); i++)
		{
			if (m_buffers[i])
				delete m_buffers[i];
		}

		glDeleteVertexArrays(1, &m_arrayID);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_arrayID);
	}
	void VertexArray::unbind() 
	{
		glBindVertexArray(0);
	}

	void VertexArray::addBuffer(Buffer* buffer, GLuint index)
	{
		bind();
		buffer->bind();

		glVertexAttribPointer(index,
			buffer->getComponentCount(), // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glEnableVertexAttribArray(index);

		buffer->unbind();
		unbind();

		m_buffers.push_back(buffer);
	}
}