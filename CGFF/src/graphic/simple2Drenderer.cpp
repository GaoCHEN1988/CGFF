#include "simple2Drenderer.h"


namespace CGFF {

	Simple2DRenderer::Simple2DRenderer()
		:Renderer2D()
	{
		initializeOpenGLFunctions();
	}
	Simple2DRenderer::~Simple2DRenderer()
	{
	}
	
	void Simple2DRenderer::submit(QSharedPointer<Renderable2D> renderable)
	{
		m_renderQueue.push_back(renderable);
	}
	void Simple2DRenderer::flush() 
	{
		while (!m_renderQueue.empty())
		{
			QSharedPointer<StaticSprite> renderable = qSharedPointerCast<StaticSprite>(m_renderQueue.front());

			renderable->getVAO()->bind();
			renderable->getIBO()->bind();

			glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_INT, 0);

			renderable->getVAO()->unbind();
			renderable->getIBO()->unbind();

			m_renderQueue.pop_front();
		}
	}

}
