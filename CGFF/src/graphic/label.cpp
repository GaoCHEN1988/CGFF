#include "label.h"
#include <QPainter>

namespace CGFF {

	Label::Label(QString text, float x, float y, int width, int height, QVector4D color)
		: Renderable2D()
		, m_text(text)
	{
		m_position = QVector3D(x, y, 0);
		m_color = color;
        m_size = QVector2D(width, height);
	}

	void Label::submit(QSharedPointer<Renderer2D> renderer)
	{
        renderer->drawString(m_text, m_position, (int)m_size.x(), (int)m_size.y(),  m_color);
	}

    void Label::setText(const QString& text)
    {
        m_text = text;
    }
}