#ifndef APPLICATION_WIDGET_H
#define APPLICATION_WIDGET_H

#include "utils/qtopengl.h"
#include "graphic/layer/layer.h"
#include "Debug/debugLayer.h"
#include <QOpenGLWidget>
#include <QTime>

class ApplicationWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    ApplicationWidget(QWidget *parent);
    ~ApplicationWidget() {};

    inline static ApplicationWidget* getApplication() { return m_instance; }

    void pushLayer(QSharedPointer<CGFF::Layer> layer);
    QSharedPointer<CGFF::Layer> popLayer();
    QSharedPointer<CGFF::Layer> popLayer(QSharedPointer<CGFF::Layer> layer);

    void pushOverlay(QSharedPointer<CGFF::Layer> layer);
    QSharedPointer<CGFF::Layer> popOverlay();
    QSharedPointer<CGFF::Layer> popOverlay(QSharedPointer<CGFF::Layer> layer);

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
    QSharedPointer<CGFF::Layer> m_debugLayer;

    static ApplicationWidget * m_instance;
};

#endif