#include "indexBuffer.h"

namespace CGFF {

	IndexBuffer::IndexBuffer(QOpenGLFunctions_4_4_Core * f, GLuint * data, GLsizei count)
		: m_function(f)
		, m_count(count)
	{
		m_function->glGenBuffers(1, &m_indexBufferID);
		m_function->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		m_function->glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
		m_function->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	IndexBuffer::~IndexBuffer() 
	{
		m_function->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::bind() 
	{
		m_function->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	}
	void IndexBuffer::unbind() 
	{
		m_function->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}