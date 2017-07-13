#include "label.h"
#include <QPainter>

namespace CGFF {

	Label::Label(QString text, float x, float y, QVector4D color)
		: Renderable2D()
		, m_text(text)
	{
		m_position = QVector3D(x, y, 0);
		m_color = color;
	}

	void Label::submit(QSharedPointer<Renderer2D> renderer)
	{
        int width = 150;
        int height = 32;

        // create the QImage and draw txt into it
        QImage textimg(width, height, QImage::Format_ARGB32);
        {
            QPainter painter(&textimg);
            textimg.fill(Qt::transparent);
            painter.setBrush(QColor(m_color.x() * 255, m_color.y() * 255, m_color.z() * 255, m_color.w() * 255));
            painter.setPen(QColor(m_color.x() * 255, m_color.y() * 255, m_color.z() * 255, m_color.w() * 255));
            painter.setFont(QFont("Sans", 20));
            painter.drawText(0, height, m_text);
        }

        m_strTexture = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(textimg.mirrored()));
        renderer->drawString(m_strTexture, m_position, width, height,  m_color);
	}

    void Label::setText(const QString& text)
    {
        m_text = text;
    }
}