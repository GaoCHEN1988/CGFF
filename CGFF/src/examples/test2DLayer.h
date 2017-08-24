#ifndef TEST_2D_LAYER_H
#define TEST_2D_LAYER_H

#include "graphic/layer/layer2D.h"
#include "graphic/sprite.h"
#include "graphic/label.h"
#include <QTime>

namespace CGFF {
    class Test2DLayer : public Layer2D
    {
    public:
        Test2DLayer(QSize size, QObject *parent = Q_NULLPTR);
        virtual ~Test2DLayer() {};

        void init() override;
        void resize(int width, int height) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
		void closeEvent(QEvent *event) override;

		virtual bool event(QEvent *event) override;

    private:
        QSharedPointer<CGFF::Sprite> m_sprite;
        QSharedPointer<CGFF::Sprite> m_sprite2;
        QSharedPointer<CGFF::Mask> m_mask;
        QSize m_size;
    };
}

#endif
