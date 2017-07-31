#ifndef WIDGET_H
#define WIDGET_H

#include "internalUI.h"

namespace CGFF {
    namespace UI {

	class Widget
	{
	private:
		Widget() {}
	protected:
		Widget(const QRect& bounds);
        virtual ~Widget() {};

	public:
		virtual bool onMousePressed(QMouseEvent* e);
		virtual bool onMouseReleased(QMouseEvent* e);
		virtual bool onMouseMoved(QMouseEvent* e);

		virtual void update();
		virtual void render(QSharedPointer<Renderer2D>& renderer);

		inline const QRect& getBounds() const { return m_bounds; }
		inline void setBounds(const QRect& bounds) { m_bounds = bounds; }

		inline bool isActive() const { return m_active; }
		inline void setActive(bool active) { m_active = active; }

    protected:
        bool m_active;
        bool m_focused;

        QRect m_bounds;
	};

} } 

#endif