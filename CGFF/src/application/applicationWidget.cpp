#include "application/applicationWidget.h"
#include "examples/test2DLayer.h"
#include "examples/test3DLayer.h"

ApplicationWidget::ApplicationWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
}

void ApplicationWidget::initializeGL()
{
#ifdef OPENGL_ES
#else
    QSurfaceFormat qFormat = QOpenGLWidget::format();
    qFormat.setProfile(QSurfaceFormat::CoreProfile);
    qFormat.setVersion(4, 4);
    QOpenGLContext::currentContext()->setFormat(qFormat);
#endif

    // initialize OpenGL
    CGFF::GL = QOpenGLContext::currentContext()->functions();
    CGFF::GL->initializeOpenGLFunctions();

    m_layerStack.append(QSharedPointer<CGFF::Layer>(new CGFF::Test3DLayer()));

    m_overLayerStack.append(QSharedPointer<CGFF::Layer>(new CGFF::Test2DLayer(this->size())));

    m_debugLayer = QSharedPointer<CGFF::Layer>(new CGFF::DebugLayer(this->size()));


    for (auto layer : m_layerStack)
    {
        layer->init();
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->init();
    }

    m_debugLayer->init();

}

void ApplicationWidget::paintGL()
{
    CGFF::GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CGFF::GL->glEnable(GL_BLEND);
    //CGFF::GL->glEnable(GL_DEPTH_TEST);
    CGFF::GL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    for (auto layer: m_layerStack)
    {
        layer->render();
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->render();
    }

    m_debugLayer->render();
}

void ApplicationWidget::resizeGL(int width, int height)
{
    for (auto layer : m_layerStack)
    {
        layer->resize(width, height);
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->resize(width, height);
    }

    m_debugLayer->resize(width, height);
}

void ApplicationWidget::mousePressEvent(QMouseEvent *event) 
{
    for (auto layer : m_layerStack)
    {
        layer->mousePressEvent(event);
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->mousePressEvent(event);
    }
    update();
}

void ApplicationWidget::mouseMoveEvent(QMouseEvent *event)
{
    for (auto layer : m_layerStack)
    {
        layer->mouseMoveEvent(event);
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->mouseMoveEvent(event);
    }
    update();
}

void ApplicationWidget::mouseReleaseEvent(QMouseEvent *event)
{
    for (auto layer : m_layerStack)
    {
        layer->mouseReleaseEvent(event);
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->mouseReleaseEvent(event);
    }
    update();
}

void ApplicationWidget::keyPressEvent(QKeyEvent *event)
{
    for (auto layer : m_layerStack)
    {
        layer->keyPressEvent(event);
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->keyPressEvent(event);
    }
    update();
}