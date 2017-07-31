#include "widget.h"

namespace CGFF {
    namespace UI {

	Widget::Widget(const QRect& bounds)
		: m_bounds(bounds)
        , m_active(true)
        , m_focused(false)
	{
	}

	bool Widget::onMousePressed(QMouseEvent* e)
	{
		return false;
	}

	bool Widget::onMouseReleased(QMouseEvent* e)
	{
		return false;
	}

	bool Widget::onMouseMoved(QMouseEvent* e)
	{
		return false;
	}

	void Widget::update()
	{
	}

	void Widget::render(QSharedPointer<Renderer2D>& renderer)
	{
	}

} }