#include "label.h"


namespace CGFF {

	Label::Label(std::string text, float x, float y, QVector4D color)
		: Renderable2D()
		, m_text(text)
	{
		m_position = QVector3D(x, y, 0);
		m_color = color;
	}

	void Label::submit(QSharedPointer<Renderer2D> renderer)
	{
		renderer->drawString(m_text, m_position, m_color);
	}

    void Label::setText(const std::string& text)
    {
        m_text = text;
    }
}