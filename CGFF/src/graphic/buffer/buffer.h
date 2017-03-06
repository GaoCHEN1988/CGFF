#ifndef BUFFER_H
#define BUFFER_H

#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLBuffer>

namespace CGFF {
	class Buffer
	{
	public:
		Buffer();
		~Buffer();
		void bind();
		void unbind();
	private:
		GLuint m_bufferID;
	};
}

#endif
