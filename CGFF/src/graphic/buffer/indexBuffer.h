#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "buffer.h"

namespace CGFF {
	class IndexBuffer : protected QOpenGLFunctions_4_4_Core
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(GLuint * data, GLsizei count);
		~IndexBuffer();
		void bind();
		void unbind();
		inline GLuint getCount() {
			return m_count;
		}
	private:

		GLuint m_indexBufferID;
		GLuint m_count;
	};
}

#endif
