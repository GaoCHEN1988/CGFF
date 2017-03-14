#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "renderable2d.h"
#include <QSharedPointer>

namespace CGFF {
	class Renderer2D
	{
	protected:
		virtual void submit(QSharedPointer<Renderable2D> renderable) = 0;
		virtual void flush() = 0;
	};
}

#endif