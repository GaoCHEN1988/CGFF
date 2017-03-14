#include "indexBuffer.h"

namespace CGFF {

	IndexBuffer::IndexBuffer(GLuint * data, GLsizei count)
		: m_count(count)
	{
		initializeOpenGLFunctions();
		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	IndexBuffer::~IndexBuffer() 
	{
		glDeleteBuffers(1, &m_indexBufferID);
	}

	void IndexBuffer::bind() 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	}
	void IndexBuffer::unbind() 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}