#include "debugLayer.h"
#include "graphic/shader/shaderFactory.h"
#include "applicationWindow.h"

namespace CGFF {

	DebugLayer* DebugLayer::s_instance = nullptr;

    DebugLayer::DebugLayer(QSize screenSize)
        : Layer2D()
    {
        m_isVisible = false;
		s_instance = this;
    }

    void DebugLayer::init()
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::SCREEN);

		//Test
		m_FPSLabel = QSharedPointer<Label>(new Label("fps", 10, g_openglWidgetSize.height() - 50, 150, 32, QVector4D(1, 1, 1, 1)));
		m_memoryUsageLabel = QSharedPointer<Label>(new Label("memory", 200, g_openglWidgetSize.height() - 50, 150, 32, QVector4D(1, 1, 1, 1)));
		m_frametimeLabel = QSharedPointer<Label>(new Label("frametime", 390, g_openglWidgetSize.height() - 50, 150, 32, QVector4D(1, 1, 1, 1)));

		add(m_FPSLabel);
		add(m_memoryUsageLabel);
		add(m_frametimeLabel);

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

	void DebugLayer::tick()
	{
		if (m_FPSLabel)
			m_FPSLabel->setText("FPS: "+QString::number(ApplicationWindow::getApplication()->getFPS()));
	}

    void DebugLayer::resize(int width, int height)
    {
		if(m_FPSLabel)
			m_FPSLabel->position.setY(g_openglWidgetSize.height() - 50);
		if (m_memoryUsageLabel)
			m_memoryUsageLabel->position.setY(g_openglWidgetSize.height() - 50);
		if (m_frametimeLabel)
			m_frametimeLabel->position.setY(g_openglWidgetSize.height() - 50);
		Layer2D::resize(width, height);
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

	void DebugLayer::closeEvent(QEvent *event)
	{
		Layer2D::closeEvent(event);
		DebugMenu::get()->closeEvent(event);
		m_tempSprites.clear();
		m_FPSLabel.clear();
		m_memoryUsageLabel.clear();
		m_frametimeLabel.clear();
	}
}