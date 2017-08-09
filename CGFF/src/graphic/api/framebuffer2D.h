#ifndef FRAMEBUFFER_2D_H
#define FRAMEBUFFER_2D_H

#include "maths/qtmaths.h"
#include <QOpenGLFramebufferObject>

namespace CGFF {

	class Framebuffer2D
	{
	public:
		virtual void setClearColor(const QMatrix4x4& color) = 0;
	public:
		static QSharedPointer<Framebuffer2D> create(int width, int height);
	};
}

#endif