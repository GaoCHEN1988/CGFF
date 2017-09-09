#ifndef LAYER_H
#define LAYER_H

#include "maths/qtmaths.h"
#include <QWidget>

namespace CGFF {
	class Layer : public QWidget
	{
	public:
        Layer(QWidget *parent = Q_NULLPTR);
		virtual ~Layer();
        virtual void init();
		virtual void render();
        virtual void update();
        virtual void tick();

        inline bool isVisible() const { return m_isVisible; }
        inline void setVisible(bool visible) { m_isVisible = visible; }

    protected:
        bool m_isVisible;
	};
}

#endif