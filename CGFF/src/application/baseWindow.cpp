#include "baseWindow.h"
#include "graphic/renderer/renderer.h"
#include <QCoreApplication>

BaseWindow::BaseWindow(QWidget * parent, CGFF::RenderAPI api)
    : QWindow()
    , m_framePerSecond(0)
    , m_fps_count(0)
    , m_timer_id(0)
    , m_parent(parent)
    , m_isActive(false)
    , m_model(nullptr)
{
    resize(800, 800);
    setMinimumSize(QSize(400, 400));

    CGFF::Context::setRenderAPI(api);
    switch (api)
    {
    case CGFF::RenderAPI::OPENGL:
        setSurfaceType(QWindow::OpenGLSurface);
        break;
    case CGFF::RenderAPI::DIRECT3D:
        break;
    }

    m_timer_id = startTimer(0);
}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::initialize()
{
    CGFF::Renderer::init();
    setupLayers();
    m_time.start();
    m_framePerSecond = 0;
    m_fps_count = 0;

    emit initilizeSignal();

    for (auto layer : m_layerStack)
    {
        layer->init();
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->init();
    }
}

void BaseWindow::update()
{
    for (auto layer : m_layerStack)
    {
        layer->update();
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->update();
    }
}

void BaseWindow::render()
{
    for (auto layer : m_layerStack)
    {
        layer->render();
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->render();
    }
}

void BaseWindow::tick()
{
    for (auto layer : m_layerStack)
    {
        layer->tick();
    }

    for (auto overLayer : m_overLayerStack)
    {
        overLayer->tick();
    }
}

void BaseWindow::renderLater() {}
void BaseWindow::renderNow()
{
    if (!CGFF::Context::isInitialized())
    {
        setUpContext();
        initialize();
    }

    CGFF::Renderer::clear(CGFF::RendererBufferType::RENDERER_BUFFER_COLOR | CGFF::RendererBufferType::RENDERER_BUFFER_DEPTH);
    CGFF::Renderer::setDepthTesting(true);
    update();
    render();

    CGFF::Renderer::present();
}

void BaseWindow::clearLayers()
{
    m_layerStack.clear();
    m_overLayerStack.clear();
}

void BaseWindow::pushLayer(QSharedPointer<CGFF::Layer> layer)
{
    m_layerStack.append(layer);
}

QSharedPointer<CGFF::Layer> BaseWindow::popLayer()
{
    QSharedPointer<CGFF::Layer> layer = m_layerStack.back();
    m_layerStack.pop_back();
    return layer;
}

QSharedPointer<CGFF::Layer> BaseWindow::popLayer(QSharedPointer<CGFF::Layer> layer)
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

void BaseWindow::pushOverlay(QSharedPointer<CGFF::Layer> layer)
{
    m_overLayerStack.append(layer);
}

QSharedPointer<CGFF::Layer> BaseWindow::popOverlay()
{
    QSharedPointer<CGFF::Layer> layer = m_overLayerStack.back();
    m_overLayerStack.pop_back();
    return layer;
}

QSharedPointer<CGFF::Layer> BaseWindow::popOverlay(QSharedPointer<CGFF::Layer> layer)
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

void BaseWindow::onActivate()
{
    m_isActive = true;
}
void BaseWindow::onDisactivate()
{
    m_isActive = false;
}

void BaseWindow::timerEvent(QTimerEvent *event)
{
    renderNow();

    // FPS count
    ++m_fps_count;
    int elapsed = m_time.elapsed();
    if (elapsed >= 1000)
    {
        m_framePerSecond = m_fps_count;
        m_fps_count = 0;
        m_time.restart();
        tick();
    }
}

bool BaseWindow::event(QEvent *event)
{
    if (!m_isActive)
        return QWindow::event(event);

    for (auto layer : m_layerStack)
    {
        QCoreApplication::sendEvent(layer.data(), event);
    }

    for (auto overLayer : m_overLayerStack)
    {
        QCoreApplication::sendEvent(overLayer.data(), event);
    }

    return QWindow::event(event);
}

void BaseWindow::setUpContext()
{
    CGFF::Context::create(this);
}
