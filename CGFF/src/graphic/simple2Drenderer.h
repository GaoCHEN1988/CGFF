#ifndef SIMPLE_2D_RENDERER_H
#define SIMPLE_2D_RENDERER_H

#include "renderer2d.h"
#include "../maths/qtmaths.h"
#include "staticSprite.h"
#include <deque>

namespace CGFF {

	class Simple2DRenderer : public Renderer2D, protected QOpenGLFunctions_4_4_Core
	{
	private:
		std::deque<QSharedPointer<Renderable2D>> m_renderQueue;
	public:
		Simple2DRenderer();
		~Simple2DRenderer();
		void submit(QSharedPointer<Renderable2D> renderable) override;
		void flush() override;

	};
	
}

#endif
