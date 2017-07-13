#ifndef TEST_2D_LAYER_H
#define TEST_2D_LAYER_H

#include "graphic/layer/layer2D.h"
#include "graphic/sprite.h"
#include "graphic/label.h"
#include <QTime>
#include <QTime>

namespace CGFF {
    class Test2DLayer : public Layer2D
    {
    public:
        Test2DLayer(QSize size);
        virtual ~Test2DLayer() {};

        void init() override;
        void render() override;

        void resize(int width, int height) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:
        QSharedPointer<CGFF::BatchRenderer2D> m_batch;
        QVector<QSharedPointer<QOpenGLTexture> > m_vTextures;
        QSharedPointer<CGFF::Sprite> m_sprite;
        QSharedPointer<CGFF::Mask> m_mask;
        QTime m_time;
        int m_frameCount;
        int last_count;
        QSharedPointer<CGFF::Label> m_fpsLabel;
        QSize m_size;
    };
}

#endif
