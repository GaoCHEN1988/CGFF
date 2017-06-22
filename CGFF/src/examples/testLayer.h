#ifndef TEST_LAYER_H
#define TEST_LAYER_H

#include "../graphic/batchRenderer2d.h"
#include "../maths/qtmaths.h"
#include "../graphic/renderable2d.h"
#include "../graphic/sprite.h"
#include "../graphic/layer/tileLayer.h"
#include "../graphic/layer/group.h"
#include "../graphic/postfx/postEffects.h"
#include "../graphic/label.h"

#include <QTime>
#include <QOpenGLWidget>

class TestLayer : public QOpenGLWidget
{
    Q_OBJECT

public:

    TestLayer(QWidget *parent = 0);
    ~TestLayer() {};

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    QMatrix4x4 m_proj;
    QMatrix4x4 m_model;

    QSharedPointer<QOpenGLShaderProgram> m_shaderProgram;
    QSharedPointer<CGFF::BatchRenderer2D> m_batch;
    QVector<QSharedPointer<QOpenGLTexture> > m_vTextures;
    QSharedPointer<CGFF::Layer> m_layer;
    QSharedPointer<CGFF::Sprite> m_sprite;
    QSharedPointer<CGFF::Mask> m_mask;
    QTime m_time;
    int m_frameCount;
    int last_count;
    QSharedPointer<CGFF::Label> m_fpsLabel;

};


#endif
