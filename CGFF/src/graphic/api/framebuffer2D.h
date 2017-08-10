#ifndef FRAMEBUFFER_2D_H
#define FRAMEBUFFER_2D_H

#include "framebuffer.h"

namespace CGFF {

	class Framebuffer2D : public Framebuffer
	{
	public:
		virtual void setClearColor(const QVector4D& color) = 0;
	public:
		static QSharedPointer<Framebuffer2D> create(int width, int height);
	};
}

#endif