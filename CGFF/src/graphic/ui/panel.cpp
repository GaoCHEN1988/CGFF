#include "panel.h"
#include "application/applicationWidget.h"

namespace CGFF {
    namespace UI {

	Panel::Panel()
		: Layer2D(QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D(ApplicationWidget::getApplication()->size())))
	{
        //ApplicationWidget::getApplication()->pushOverlay(QSharedPointer<Panel>(this));
	}

	Panel::~Panel()
	{
        //ApplicationWidget::getApplication()->popOverlay(QSharedPointer<CGFF::Layer>(this));
	}

	QSharedPointer<Widget> Panel::add(QSharedPointer<Widget> widget)
	{
		m_widgets.push_back(widget);
		return widget;
	}

	void Panel::remove(QSharedPointer<Widget> widget)
	{
        //Need to be tested
		for (uint i = 0; i < m_widgets.size(); i++)
		{
			if (m_widgets[i] == widget)
			{
				m_widgets.remove(i);
				break;
			}
		}
	}

	void Panel::clear()
	{
		m_widgets.clear();
	}

	void Panel::mousePressEvent(QMouseEvent* e)
	{
        QPoint mouse(e->x(), (g_openglWidgetSize.height() - e->y()));
		for (uint i = 0; i < m_widgets.size(); i++)
		{
			QSharedPointer<Widget> widget = m_widgets[i];
			if (widget->getBounds().contains(mouse))
			{
				if (widget->onMousePressed(e))
					return;
			}
		}
	}

	void Panel::mouseReleaseEvent(QMouseEvent* e)
	{
        QPoint mouse(e->x(), (g_openglWidgetSize.height() - e->y()));
		for (uint i = 0; i < m_widgets.size(); i++)
		{
			QSharedPointer<Widget> widget = m_widgets[i];
			if (widget->getBounds().contains(mouse))
			{
				if (widget->onMouseReleased(e))
					return;
			}
		}
	}

	void Panel::mouseMoveEvent(QMouseEvent* e)
	{
		for (uint i = 0; i < m_widgets.size(); i++)
		{
			QSharedPointer<Widget> widget = m_widgets[i];
			if (widget->onMouseMoved(e))
				return;
		}
	}

	void Panel::update()
	{
		for (QSharedPointer<Widget> widget : m_widgets)
		{
			if (widget->isActive())
				widget->update();
		}
	}

	void Panel::render(QSharedPointer<Renderer2D>& renderer)
	{
		for (QSharedPointer<Widget> widget : m_widgets)
		{
			if (widget->isActive())
				widget->render(renderer);
		}
	}

} }