#include "slider.h"
#include "application/applicationWidget.h"

namespace CGFF {
    namespace UI {

	Slider::Slider(const QRect& bounds, bool vertical)
		: Widget(bounds)
        , m_value(0.0f)
        , m_state(SliderState::UNPRESSED)
        , m_headOffset(0.0f)
        , m_callback(&Slider::noCallback)
        , m_vertical(vertical)
	{
		float size = vertical ? bounds.width() : bounds.height();
		m_headBounds = QRect(bounds.x(), bounds.y(), size, size);
	}

	Slider::Slider(const QRect& bounds, float value, const ValueChangedCallback& callback, bool vertical)
		: Widget(bounds)
        , m_value(value)
        , m_state(SliderState::UNPRESSED)
        , m_headOffset(0.0f)
        , m_callback(callback)
        , m_vertical(vertical)
	{
		float size = vertical ? bounds.width() : bounds.height();
		m_headBounds = QRect(bounds.x(), bounds.y(), size, size);
	}

	bool Slider::onMousePressed(QMouseEvent* e)
	{
		// TODO: remove these hard coded mouse maths throughout the engine
        QPoint mouse(e->x(), (g_openglWidgetSize.height() - e->y()));
		if (m_headBounds.contains(mouse))
		{
			m_state = SliderState::PRESSEDHEAD;
			m_headOffset = m_vertical ? (mouse.y() - m_headBounds.y()) : (mouse.x() - m_headBounds.x());
		}
		else
		{
			m_state = SliderState::PRESSED;
		}
		return true;
	}

	bool Slider::onMouseReleased(QMouseEvent* e)
	{
		m_state = SliderState::UNPRESSED;
		return true;
	}

	bool Slider::onMouseMoved(QMouseEvent* e)
	{
		// TODO: remove these hard coded mouse maths throughout the engine
        QPoint mouse(e->x(), (g_openglWidgetSize.height() - e->y()));
		if (m_state == SliderState::PRESSEDHEAD)
		{
			if (m_vertical)
				setValue((mouse.y() - m_bounds.y() - m_headOffset) / (m_bounds.height() - m_headBounds.height()));
			else
				setValue((mouse.x() - m_bounds.x() - m_headOffset) / (m_bounds.width() - m_headBounds.width()));
		}

		return false;
	}

	void Slider::update()
	{
		//if (!Input::IsMouseButtonPressed(SP_MOUSE_LEFT))
		//	m_state = SliderState::UNPRESSED;

		if (m_vertical)
		{
			float bounds = m_bounds.height() - m_headBounds.height();
			m_headBounds.moveTop(m_bounds.y() + bounds * m_value);
			m_headBounds.moveTop(qBound(m_bounds.y(), m_headBounds.y(), m_bounds.y() + m_bounds.height() - m_headBounds.height()));
		}
		else
		{
			float bounds = m_bounds.width() - m_headBounds.width();
			m_headBounds.moveLeft(m_bounds.x() + bounds * m_value);
			m_headBounds.moveLeft(qBound(m_bounds.x(), m_headBounds.x(), m_bounds.x() + m_bounds.width() - m_headBounds.width()));
		}
	}

	void Slider::render(QSharedPointer<Renderer2D>& renderer)
	{
		renderer->fillRect(m_bounds, QVector4D(0.498f, 0.498f, 0.498f, 0.498f));
		renderer->drawRect(m_bounds);

		renderer->fillRect(m_headBounds, QVector4D(0.984f, 0.984f, 0.984f, 0.984f));
		renderer->drawRect(m_headBounds);

		QPoint offset = m_vertical ? QPoint(0, m_bounds.height() / 2.0f) : QPoint(m_bounds.width() / 2.0f, 0);
		renderer->drawLine(QVector2D(m_bounds.center().x() - offset.x(), m_bounds.center().y() - offset.y()), 
            QVector2D(m_bounds.center().x() + offset.x(), m_bounds.center().y() + offset.y()));
	}

	void Slider::setValue(float value)
	{
		value = qBound(0.0f, value, 1.0f);
		m_value = value;
		m_callback(value);
	}

} }