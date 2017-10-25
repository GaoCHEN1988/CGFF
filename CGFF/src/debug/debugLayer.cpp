#include "debugLayer.h"
#include "graphic/shader/shaderFactory.h"
#include "debugWindow.h"

namespace CGFF {

	DebugLayer* DebugLayer::s_instance = nullptr;

    DebugLayer::DebugLayer(QSize screenSize, QWidget *parent)
        : Layer2D(screenSize, parent)
    {
        m_isVisible = false;
		s_instance = this;
    }

    void DebugLayer::init()
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::SCREEN);

		//Test
		m_FPSLabel = QSharedPointer<Label>(new Label("FPS", 10, m_size.height() - 50, 150, 32, QVector4D(1, 1, 1, 1)));
		//m_memoryUsageLabel = QSharedPointer<Label>(new Label("memory", 300, m_size.height() - 50, 150, 32, QVector4D(1, 1, 1, 1)));
		//m_frametimeLabel = QSharedPointer<Label>(new Label("frametime", 500, m_size.height() - 50, 150, 32, QVector4D(1, 1, 1, 1)));

		add(m_FPSLabel);
		//add(m_memoryUsageLabel);
		//add(m_frametimeLabel);

        //DebugMenu::init(m_size);
        //DebugMenu::setVisible(true);
    }

    void DebugLayer::render(QSharedPointer<Renderer2D>& renderer)
    {
        //if (DebugMenu::isVisible())
        //{
        //    DebugMenu::get()->render(renderer);
        //}

		m_tempSprites.clear();
    }

	void DebugLayer::tick()
	{
		if (m_FPSLabel)
			m_FPSLabel->setText("FPS: "+QString::number(DebugWindow::getApplication()->getFPS()));
	}

	void DebugLayer::resizeEvent(QResizeEvent *event)
	{
		QSize s = event->size();
		if(m_FPSLabel)
			m_FPSLabel->position.setY(s.height() - 50);
		if (m_memoryUsageLabel)
			m_memoryUsageLabel->position.setY(s.height() - 50);
		if (m_frametimeLabel)
			m_frametimeLabel->position.setY(s.height() - 50);

		Layer2D::resizeEvent(event);

		//if (DebugMenu::isVisible())
		//{
		//	DebugMenu::get()->resizeEvent(event);
		//}
	}

    void DebugLayer::mousePressEvent(QMouseEvent *event)
    {
        //if (DebugMenu::isVisible())
        //{
        //    DebugMenu::get()->mousePressEvent(event);
        //}
    }

    void DebugLayer::mouseMoveEvent(QMouseEvent *event) 
    {
        //if (DebugMenu::isVisible())
        //{
        //    DebugMenu::get()->mouseMoveEvent(event);
        //}
    }

    void DebugLayer::mouseReleaseEvent(QMouseEvent *event)
    {
        //if (DebugMenu::isVisible())
        //{
        //    DebugMenu::get()->mouseReleaseEvent(event);
        //}
    }

    void DebugLayer::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Control)
        {
            m_isVisible = !m_isVisible;
            //DebugMenu::setVisible(m_isVisible);
        }
    }

    void DebugLayer::update()
    {
        //if (DebugMenu::isVisible())
        //{
        //    DebugMenu::get()->update();
        //}
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

	void DebugLayer::closeEvent(QCloseEvent *event)
	{
		//Layer2D::closeEvent(event);
		////DebugMenu::get()->closeEvent(event);
		//m_tempSprites.clear();
		//m_FPSLabel.clear();
		//m_memoryUsageLabel.clear();
		//m_frametimeLabel.clear();
	}

}