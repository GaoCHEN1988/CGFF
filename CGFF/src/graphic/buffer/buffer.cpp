#include "buffer.h"

namespace CGFF {

	Buffer::Buffer(QOpenGLFunctions_4_4_Core * f, GLfloat * data, GLsizei count, GLuint componentCount)
		:m_componentCount(componentCount)
		, m_function(f)
	{
		m_function->glGenBuffers(1, &m_bufferID);
		m_function->glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		m_function->glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
		m_function->glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer() 
	{
		m_function->glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Buffer::bind()
	{
		m_function->glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

	}
	void Buffer::unbind() 
	{
		m_function->glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}