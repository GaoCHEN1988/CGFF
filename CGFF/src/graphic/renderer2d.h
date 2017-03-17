#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "renderable2d.h"
#include <QSharedPointer>

namespace CGFF {
	class Renderer2D
	{
	protected:
		Renderer2D()
		{
			m_transformationStack.push_back(QMatrix4x4());
		}
	public:
		virtual void submit(QSharedPointer<Renderable2D> renderable) = 0;
		virtual void flush() = 0;
		virtual void begin() {}
		virtual void end() {}

		void push(QMatrix4x4 matrix, bool override = false)
		{
			if(override)
				m_transformationStack.push_back(matrix);
			else
				m_transformationStack.push_back(m_transformationStack.back()*matrix);
		}

		void pop() 
		{
			if(m_transformationStack.size()>0)
				m_transformationStack.pop_back();

			//To do: Add to log system
		}

	protected:
		std::vector<QMatrix4x4> m_transformationStack;
	};
}

#endif