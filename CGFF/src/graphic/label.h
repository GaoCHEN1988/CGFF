#ifndef LABEL_H
#define LABEL_H

#include "renderable2d.h"

namespace CGFF {

	class Label : public Renderable2D
	{
	public:
		Label(std::string text, float x, float y, QVector4D color);

		void submit(QSharedPointer<Renderer2D> renderer) override;

        void setText(const std::string& text);
	private:
		std::string m_text;
	};

}

#endif