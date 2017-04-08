#ifndef BUFFER_H
#define BUFFER_H

#include "../utils/qtopengl.h"

namespace CGFF {
	class Buffer : protected QOpenGLFunctions_4_4_Core
	{
	public:
		Buffer() = default;
		Buffer(GLfloat * data, GLsizei count, GLuint componentCount);
		~Buffer();
		void bind();
		void unbind();

		inline GLuint getComponentCount() {
			return m_componentCount;
		}

	private:

		GLuint m_bufferID;
		GLuint m_componentCount;
	};
}

#endif
