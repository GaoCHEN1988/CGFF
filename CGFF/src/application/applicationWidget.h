#ifndef APPLICATION_WIDGET_H
#define APPLICATION_WIDGET_H

#include "utils/qtopengl.h"
#include "graphic/layer/layer.h"
#include <QOpenGLWidget>
#include <QTime>

class ApplicationWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    ApplicationWidget(QWidget *parent);
    ~ApplicationWidget() {};

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    QVector<QSharedPointer<CGFF::Layer>> m_layerStack;
    QVector<QSharedPointer<CGFF::Layer>> m_overLayerStack;
};

#endif