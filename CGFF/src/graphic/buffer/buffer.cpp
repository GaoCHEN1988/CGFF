#include "buffer.h"

namespace CGFF {

	Buffer::Buffer(GLfloat * data, GLsizei count, GLuint componentCount)
		:m_componentCount(componentCount)
	{
		initializeOpenGLFunctions();
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer() 
	{
		glDeleteBuffers(1, &m_bufferID);
	}

	void Buffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

	}
	void Buffer::unbind() 
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}