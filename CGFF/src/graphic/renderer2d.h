#ifndef RENDERER_2D_H
#define RENDERER_2D_H
#include "../maths/qtmaths.h"
#include <QSharedPointer>

namespace CGFF {

	class Renderable2D;

	class Renderer2D
	{
	protected:
		Renderer2D()
		{
			m_transformationStack.push_back(QMatrix4x4());

			m_tranformationBack = &m_transformationStack.back();
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

			m_tranformationBack = &m_transformationStack.back();
		}

		void pop() 
		{
			if(m_transformationStack.size()>0)
				m_transformationStack.pop_back();

			m_tranformationBack = &m_transformationStack.back();
			//To do: Add to log system
		}

	protected:
		std::vector<QMatrix4x4> m_transformationStack;
		QMatrix4x4* m_tranformationBack;
	};
}

#endif