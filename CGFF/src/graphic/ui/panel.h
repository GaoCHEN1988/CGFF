#ifndef PANEL_H
#define PANEL_H

#include "internalUI.h"
#include "widget.h"

namespace CGFF {
    namespace UI {

	class Panel : public Layer2D
	{
	public:
		Panel(QSize size);
		virtual ~Panel();

		QSharedPointer<Widget> add(QSharedPointer<Widget> widget);
		void remove(QSharedPointer<Widget> widget);
		void clear();
		void mousePressEvent(QMouseEvent* e) override;
        void mouseReleaseEvent(QMouseEvent* e)override;
        void mouseMoveEvent(QMouseEvent* e)override;

		void update() override;
		void render(QSharedPointer<Renderer2D>& renderer) override;

	private:
		QVector<QSharedPointer<Widget>> m_widgets;
	};

} } 

#endif