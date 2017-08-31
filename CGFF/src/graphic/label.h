#ifndef CGFF_LABEL_H
#define CGFF_LABEL_H

#include "sprite.h"

namespace CGFF {

	class Label : public Sprite
	{
	public:
		Label(QString text, float x, float y, int width, int height, QVector4D color);

		void submit(QSharedPointer<Renderer2D> renderer) override;

        void setText(const QString& text);

	public:
		QVector3D& position;

	private:
		QString m_text;
		QFont m_font;
	};

}

#endif