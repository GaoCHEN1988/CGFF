#include "application/applicationWidget.h"
#include "examples/test2DLayer.h"
#include "examples/test3DLayer.h"

ApplicationWidget * ApplicationWidget::m_instance = nullptr;

ApplicationWidget::ApplicationWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
    m_instance = this;
}

void ApplicationWidget::pushLayer(QSharedPointer<CGFF::Layer> layer)
{
    m_layerStack.append(layer);
    layer->init();
}
QSharedPointer<CGFF::Layer> ApplicationWidget::popLayer()
{
    QSharedPointer<CGFF::Layer> layer = m_layerStack.back();
    m_layerStack.pop_back();
    return layer;
}
QSharedPointer<CGFF::Layer> ApplicationWidget::popLayer(QSharedPointer<CGFF::Layer> layer)
{
    for (uint i = 0; i < m_layerStack.size(); i++)
    {
        if (m_layerStack[i] == layer)
        {
            m_layerStack.remove(i);
            break;
        }
    }
    return layer;
}

void ApplicationWidget::pushOverlay(QSharedPointer<CGFF::Layer> layer) 
{
    m_overLayerStack.append(layer);
    layer->init();
}
QSharedPointer<CGFF::Layer> ApplicationWidget::popOverlay()
{
    QSharedPointer<CGFF::Layer> layer = m_overLayerStack.back();
    m_overLayerStack.pop_back();
    return layer;
}
QSharedPointer<CGFF::Layer> ApplicationWidget::popOverlay(QSharedPointer<CGFF::Layer> layer)
{
    for (uint i = 0; i < m_overLayerStack.size(); i++)
    {
        if (m_overLayerStack[i] == layer)
        {
            m_overLayerStack.remove(i);
            break;
        }
    }
    return layer;
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

    CGFF::openglWidgetSize = this->size();

    // initialize OpenGL
    CGFF::GL = QOpenGLContext::currentContext()->functions();
    CGFF::GL->initializeOpenGLFunctions();

    m_debugLayer = QSharedPointer<CGFF::Layer>(new CGFF::DebugLayer(this->size()));

    m_debugLayer->init();

    pushLayer(QSharedPointer<CGFF::Layer>(new CGFF::Test3DLayer()));

    pushOverlay(QSharedPointer<CGFF::Layer>(new CGFF::Test2DLayer(this->size())));
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

    if (m_debugLayer->isVisible())
    {
        m_debugLayer->update();
        m_debugLayer->render();
    }
        
}

void ApplicationWidget::resizeGL(int width, int height)
{
    CGFF::openglWidgetSize = this->size();

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

    if (m_debugLayer->isVisible())
        m_debugLayer->mousePressEvent(event);

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

    if (m_debugLayer->isVisible())
        m_debugLayer->mouseMoveEvent(event);

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

    if (m_debugLayer->isVisible())
        m_debugLayer->mouseReleaseEvent(event);

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

    m_debugLayer->keyPressEvent(event);

    update();
}