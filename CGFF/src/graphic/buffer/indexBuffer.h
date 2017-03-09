#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "buffer.h"

namespace CGFF {
	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(QOpenGLFunctions_4_4_Core * f, GLuint * data, GLsizei count);
		~IndexBuffer();
		void bind();
		void unbind();
		inline GLuint getCount() {
			return m_count;
		}
	private:
		QOpenGLFunctions_4_4_Core * m_function;
		GLuint m_indexBufferID;
		GLuint m_count;
	};
}

#endif
