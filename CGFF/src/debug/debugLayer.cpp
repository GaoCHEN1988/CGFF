#include "debugLayer.h"
#include "graphic/shader/shaderFactory.h"
#include "debugWindow.h"

namespace CGFF {

	DebugLayer* DebugLayer::s_instance = nullptr;

    DebugLayer::DebugLayer(QSize screenSize, QWidget *parent)
        : Layer2D(screenSize, parent)
        , m_FPSLabel(nullptr)
    {
        m_isVisible = false;
		s_instance = this;
    }

    void DebugLayer::init()
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::SCREEN);

        //FPS label
        m_FPSLabel = QSharedPointer<Label>(new Label("FPS", 10, m_size.height() - 50, 150, 32, QVector4D(1, 1, 1, 1)));

		add(m_FPSLabel);
    }

    void DebugLayer::render(QSharedPointer<Renderer2D>& renderer)
    {

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

		Layer2D::resizeEvent(event);
	}

    void DebugLayer::mousePressEvent(QMouseEvent *event)
    {
    }

    void DebugLayer::mouseMoveEvent(QMouseEvent *event) 
    {
    }

    void DebugLayer::mouseReleaseEvent(QMouseEvent *event)
    {
    }

    void DebugLayer::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Control)
        {
            m_isVisible = !m_isVisible;
        }
    }

    void DebugLayer::update()
    {
    }

	void DebugLayer::drawSprite(QSharedPointer<Sprite> sprite)
	{
		s_instance->submit(sprite);
	}
	void DebugLayer::drawTexture(QSharedPointer<Texture2D> texture, const QVector2D& position, const QVector2D& size)
	{
	}

	void DebugLayer::closeEvent(QCloseEvent *event)
	{
	}

}