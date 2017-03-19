#include "group.h"

namespace CGFF {

	Group::Group(const QMatrix4x4& matrix)
		: m_transformationMatrix(matrix)
	{
	}

	void Group::submit(QSharedPointer<Renderer2D> renderer) 
	{
		renderer->push(m_transformationMatrix);
		for (const QSharedPointer<Renderable2D> renderable :m_renderables)
		{
			renderable->submit(renderer);
		}
		renderer->pop();
	}

	void Group::add(QSharedPointer<Renderable2D> renderable)
	{
		m_renderables.push_back(renderable);
	}
}