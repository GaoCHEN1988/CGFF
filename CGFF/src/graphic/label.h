#ifndef CGFF_LABEL_H
#define CGFF_LABEL_H

#include "renderable2d.h"

namespace CGFF {

	class Label : public Renderable2D
	{
	public:
		Label(QString text, float x, float y, int width, int height, QVector4D color);

		void submit(QSharedPointer<Renderer2D> renderer) override;

        void setText(const QString& text);
	private:
		QString m_text;
	};

}

#endif