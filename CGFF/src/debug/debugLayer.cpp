#include "debugLayer.h"
#include "graphic/shader/shaderFactory.h"

namespace CGFF {

	DebugLayer* DebugLayer::s_instance = nullptr;

    DebugLayer::DebugLayer(QSize screenSize)
        : Layer2D(QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D(screenSize)))
    {
        m_isVisible = false;
		s_instance = this;
    }

    void DebugLayer::init()
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::SCREEN);

		//Test
		m_FPSLabel = QSharedPointer<Label>(new Label("fps", 10, g_openglWidgetSize.height() - 50, 100, 32, QVector4D(1, 1, 1, 1)));
		m_memoryUsageLabel = QSharedPointer<Label>(new Label("memory", 110, g_openglWidgetSize.height() - 50, 100, 32, QVector4D(1, 1, 1, 1)));
		m_frametimeLabel = QSharedPointer<Label>(new Label("frametime", 210, g_openglWidgetSize.height() - 50, 100, 32, QVector4D(1, 1, 1, 1)));

		add(m_FPSLabel);
		add(m_memoryUsageLabel);
		add(m_frametimeLabel);

        DebugMenu::init();
        DebugMenu::setVisible(true);
    }

	void DebugLayer::init(QSharedPointer<Renderer2D> renderer, QSharedPointer<Material> material)
	{
		renderer->setRenderTarget(CGFF::RenderTarget::SCREEN);

		//Test
		m_FPSLabel = QSharedPointer<Label>(new Label("fps", 10, g_openglWidgetSize.height() - 50, 100, 32, QVector4D(1, 1, 1, 1)));
		m_memoryUsageLabel = QSharedPointer<Label>(new Label("memory", 110, g_openglWidgetSize.height() - 50, 100, 32, QVector4D(1, 1, 1, 1)));
		m_frametimeLabel = QSharedPointer<Label>(new Label("frametime", 210, g_openglWidgetSize.height() - 50, 100, 32, QVector4D(1, 1, 1, 1)));

		add(m_FPSLabel);
		add(m_memoryUsageLabel);
		add(m_frametimeLabel);

		//Test
		DebugMenu::init();
		DebugMenu::setVisible(true);
	}

    void DebugLayer::render()
    {
        Layer2D::render();

        if (DebugMenu::isVisible())
        {
            DebugMenu::get()->render(m_renderer);
        }

		m_tempSprites.clear();
    }

    void DebugLayer::resize(int width, int height)
    {
        CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        m_projectionMatrix.setToIdentity();
        m_projectionMatrix.ortho(0, GLfloat(width), 0, GLfloat(height), 0.0f, 100.0f);
    }

    void DebugLayer::mousePressEvent(QMouseEvent *event)
    {
        if (DebugMenu::isVisible())
        {
            DebugMenu::get()->mousePressEvent(event);
        }
    }
    void DebugLayer::mouseMoveEvent(QMouseEvent *event) 
    {
        if (DebugMenu::isVisible())
        {
            DebugMenu::get()->mouseMoveEvent(event);
        }
    }
    void DebugLayer::mouseReleaseEvent(QMouseEvent *event)
    {
        if (DebugMenu::isVisible())
        {
            DebugMenu::get()->mouseReleaseEvent(event);
        }
    }

    void DebugLayer::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Control)
        {
            m_isVisible = !m_isVisible;
            DebugMenu::setVisible(m_isVisible);
        }
    }

    void DebugLayer::update()
    {
        if (DebugMenu::isVisible())
        {
            DebugMenu::get()->update();
        }
    }

	void DebugLayer::drawSprite(QSharedPointer<Sprite> sprite)
	{
		s_instance->submit(sprite);
	}
	void DebugLayer::drawTexture(QSharedPointer<Texture2D> texture, const QVector2D& position, const QVector2D& size)
	{
		QSharedPointer<Sprite> sprite = QSharedPointer<Sprite>(new Sprite(position.x(), position.y(), size.x(), size.y(), texture));
		s_instance->m_tempSprites.push_back(sprite);
		s_instance->submit(sprite);
	}
}