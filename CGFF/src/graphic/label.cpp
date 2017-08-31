#include "label.h"
#include <QPainter>

namespace CGFF {

	Label::Label(QString text, float x, float y, int width, int height, QVector4D color)
		: Sprite()
		, m_text(text)
		, position(m_position)
		, m_font(QFont("Sans"))
	{
		m_position = QVector3D(x, y, 0);
		m_color = color;
        m_size = QVector2D(width, height);
		m_font.setPixelSize(height);
	}

	void Label::submit(QSharedPointer<Renderer2D> renderer)
	{
        renderer->drawString(m_text, m_position, m_color, m_font);
	}

    void Label::setText(const QString& text)
    {
        m_text = text;
    }
}