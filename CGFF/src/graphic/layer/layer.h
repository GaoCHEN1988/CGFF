#ifndef LAYER_H
#define LAYER_H

#include "maths/qtmaths.h"

#include <QMouseEvent>
#include <QKeyEvent>

namespace CGFF {
	class Layer
	{
	public:
        Layer();
		virtual ~Layer();
        virtual void init();
		virtual void render();
        virtual void update();
        virtual void tick();

        virtual void resize(int width, int height) {};
        virtual void mousePressEvent(QMouseEvent *event) {};
        virtual void mouseMoveEvent(QMouseEvent *event) {};
        virtual void mouseReleaseEvent(QMouseEvent *event) {};
        virtual void keyPressEvent(QKeyEvent *event) {};

        inline bool isVisible() const { return m_isVisible; }
        inline void setVisible(bool visible) { m_isVisible = visible; }

    protected:
        bool m_isVisible;
	};
}

#endif