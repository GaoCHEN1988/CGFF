#ifndef BUFFER_H
#define BUFFER_H

#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLBuffer>

namespace CGFF {
	class Buffer
	{
	public:
		Buffer() = default;
		Buffer(QOpenGLFunctions_4_4_Core * f, GLfloat * data, GLsizei count, GLuint componentCount);
		~Buffer();
		void bind();
		void unbind();

		inline GLuint getComponentCount() {
			return m_componentCount;
		}

	private:
		QOpenGLFunctions_4_4_Core * m_function;
		GLuint m_bufferID;
		GLuint m_componentCount;
	};
}

#endif
