#ifndef GROUP_H
#define GROUP_H

#include "graphic/renderable2d.h"
#include "maths/qtmaths.h"

namespace CGFF {

	class Group : public Renderable2D
	{
	public: 
		Group(const QMatrix4x4& matrix);
		~Group();
		void submit(QSharedPointer<Renderer2D> renderer) override;
		void add(QSharedPointer<Renderable2D> renderable);

	private:
		QVector<QSharedPointer<Renderable2D>> m_renderables;
		QMatrix4x4 m_transformationMatrix;
	};

}

#endif