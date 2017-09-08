#include "widget.h"

namespace CGFF {
    namespace UI {

	//Widget::Widget(Widget* parent)
	//	: m_bounds()
	//	, m_screenSize(parent->m_screenSize)
	//	, m_active(true)
	//	, m_focused(false)
	//{
	//}

	Widget::Widget(const QRect& bounds, Widget* parent)
		: m_bounds(bounds)
		, m_widgetSize(parent->m_widgetSize)
		, m_active(true)
		, m_focused(false)
	{
	}

	Widget::Widget(const QSize& screenSize)
		: m_bounds()
		, m_widgetSize(screenSize)
		, m_active(true)
		, m_focused(false)
	{}
	//Widget::Widget(const QSize& screenSize, const QRect& bounds)
	//	: m_bounds(bounds)
 //       , m_active(true)
 //       , m_focused(false)
	//{
	//}

	void Widget::resize(int width, int height)
	{
		m_widgetSize = QSize(width, height);
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