#include "button.h"
#include "application/applicationWidget.h"

namespace CGFF {
    namespace UI {

	Button::Button(const QString& label, const QRect& bounds, const ActionHandler& handler)
		: Widget(bounds)
        , m_label(label)
        , m_actionHandler(handler)
        , m_state(ButtonState::UNPRESSED)
	{
		m_font = QFont("Sans");
	}

	bool Button::onMousePressed(QMouseEvent* e)
	{
		m_state = ButtonState::PRESSED;
		return true;
	}

	bool Button::onMouseReleased(QMouseEvent* e)
	{
		if (m_state == ButtonState::PRESSED)
            onAction();

		m_state = ButtonState::UNPRESSED;
		return true;
	}

	bool Button::onMouseMoved(QMouseEvent* e)
	{
		// TODO: remove these hard coded mouse maths throughout the engine
        QPoint mouse(e->x(), (openglWidgetSize.height()- e->y()));
		if (m_state == ButtonState::PRESSED && !m_bounds.contains(mouse))
  			m_state = ButtonState::UNPRESSED;

		return false;
	}

	void Button::onAction()
	{
		m_actionHandler();
	}

	void Button::update()
	{
	}

	void Button::render(QSharedPointer<Renderer2D>& renderer)
	{
		renderer->drawRect(m_bounds);

		renderer->fillRect(m_bounds, m_state == ButtonState::PRESSED ? QVector4D(0.984f, 0.733f, 0.733f, 0.733f) : QVector4D(0.498f, 0.498f, 0.498f, 0.498f));
        ////test
		renderer->drawString(m_label, QVector3D(m_bounds.topLeft().x() + 0.2f, m_bounds.topLeft().y()+0.7f, 0.0f), 300, 40, QVector4D(1.0f, 1.0f, 1.0f, 1.0f), m_font);
	}

} }