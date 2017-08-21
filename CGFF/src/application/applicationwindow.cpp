#include "applicationwindow.h"
#include "examples/test2DLayer.h"
#include "graphic/api/context.h"
#include "graphic/renderer.h"

ApplicationWindow * ApplicationWindow::m_instance = nullptr;


ApplicationWindow::ApplicationWindow(QWindow * parent, CGFF::RenderAPI api)
	: QWindow(parent) 
	, m_framePerSecond(0)
	, last_count(0)
    , m_context(nullptr)
{
    resize(800, 800);
    setMinimumSize(QSize(400, 400));
	m_instance = this;
    CGFF::Context::setRenderAPI(api);
	//Test
	setSurfaceType(QWindow::OpenGLSurface);

	timer_id_ = startTimer(0);
}

ApplicationWindow::~ApplicationWindow() 
{
    int test = 0;
}

void ApplicationWindow::initialize()
{
	CGFF::Renderer::init();

	m_debugLayer = QSharedPointer<CGFF::Layer>(new CGFF::DebugLayer(this->size()));

	m_debugLayer->init();

	pushOverlay(QSharedPointer<CGFF::Layer>(new CGFF::Test2DLayer(this->size())));

	m_time.start();
	m_framePerSecond = 0;
	last_count = 0;
}

void ApplicationWindow::render()
{
	for (auto layer : m_layerStack)
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

void ApplicationWindow::renderLater()
{
}

void ApplicationWindow::renderNow()
{
	if (!isExposed())
		return;

	//if (!CGFF::Context::isInitialized()) 
 //   {
	//	CGFF::Context::create(this);
	//	initialize();
	//}

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        QSurfaceFormat qFormat = this->requestedFormat();
        qFormat.setProfile(QSurfaceFormat::CoreProfile);
        qFormat.setVersion(4, 4);
        m_context->setFormat(qFormat);
        m_context->create();
        m_context->makeCurrent(this);
        CGFF::GL = m_context->versionFunctions<QOpenGLFunctions_4_4_Core>();
        CGFF::GL->initializeOpenGLFunctions();

        initialize();

    }

    CGFF::Renderer::clear(CGFF::RendererBufferType::RENDERER_BUFFER_COLOR | CGFF::RendererBufferType::RENDERER_BUFFER_DEPTH);

    m_context->makeCurrent(this);

	render();

    m_context->swapBuffers(this);
	//CGFF::Renderer::present();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        qFatal("opengl error!");
}

void ApplicationWindow::pushLayer(QSharedPointer<CGFF::Layer> layer)
{
	m_layerStack.append(layer);
	layer->init();
}
QSharedPointer<CGFF::Layer> ApplicationWindow::popLayer()
{
	QSharedPointer<CGFF::Layer> layer = m_layerStack.back();
	m_layerStack.pop_back();
	return layer;
}
QSharedPointer<CGFF::Layer> ApplicationWindow::popLayer(QSharedPointer<CGFF::Layer> layer)
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

void ApplicationWindow::pushOverlay(QSharedPointer<CGFF::Layer> layer)
{
	m_overLayerStack.append(layer);
	layer->init();
}
QSharedPointer<CGFF::Layer> ApplicationWindow::popOverlay()
{
	QSharedPointer<CGFF::Layer> layer = m_overLayerStack.back();
	m_overLayerStack.pop_back();
	return layer;
}
QSharedPointer<CGFF::Layer> ApplicationWindow::popOverlay(QSharedPointer<CGFF::Layer> layer)
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

void ApplicationWindow::timerEvent(QTimerEvent *event)
{
	renderNow();

	// FPS count
	++m_framePerSecond;
	int elapsed = m_time.elapsed();
	if (elapsed >= 1000)
	{
		last_count = m_framePerSecond;
		m_framePerSecond = 0;
		m_time.restart();
	}
}

void ApplicationWindow::exposeEvent(QExposeEvent *event)
{
	Q_UNUSED(event);

	if (isExposed())
		renderNow();
}

void ApplicationWindow::resizeEvent(QResizeEvent* event)
{
    if (!m_context)
        return;

	CGFF::g_openglWidgetSize = event->size();
	int width = CGFF::g_openglWidgetSize.width();
	int height = CGFF::g_openglWidgetSize.height();

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

void ApplicationWindow::mousePressEvent(QMouseEvent *event)
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
}

void ApplicationWindow::mouseMoveEvent(QMouseEvent *event)
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
}

void ApplicationWindow::mouseReleaseEvent(QMouseEvent *event)
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
}

void ApplicationWindow::keyPressEvent(QKeyEvent *event)
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
}