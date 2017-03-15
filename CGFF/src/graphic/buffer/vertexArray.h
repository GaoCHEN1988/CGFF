#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "buffer.h"
#include <vector>

namespace CGFF {
	class VertexArray : protected QOpenGLFunctions_4_4_Core
	{
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, GLuint index);
		void bind();
		void unbind();

	private:
		GLuint m_arrayID;
		std::vector<Buffer*> m_buffers;
	};
}

#endif
