#include "test2DLayer.h"
#include "graphic/shader/shaderFactory.h"
namespace CGFF {

    Test2DLayer::Test2DLayer(QSize size, QWidget *parent)
        : Layer2D(size, parent)
        , m_size(size)
    {
    }

    void Test2DLayer::init() 
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::SCREEN);
  
        m_sprite = QSharedPointer<CGFF::Sprite>(new CGFF::Sprite(0.0f, 0.0f, 100, 100, Texture2D::createFromFile("Resources/tb.png")));
        m_sprite2 = QSharedPointer<CGFF::Sprite>(new CGFF::Sprite(500.0f, 500.0f, 100.0, 100.0, Texture2D::createFromFile("Resources/particle.png")));

        Layer2D::add(m_sprite);
        Layer2D::add(m_sprite2);

        m_mask = QSharedPointer<CGFF::Mask>(new CGFF::Mask(Texture2D::createFromFile("Resources/mask.png")));
        Layer2D::setMask(m_mask);
    }

    void Test2DLayer::keyPressEvent(QKeyEvent *event) 
    {
        float speed = 10.0f;
        switch (event->key())
        {
        case (Qt::Key_W) :
        {
            m_sprite->position.setY(m_sprite->position.y() + speed);
            break;
        }
        case (Qt::Key_S) :
        {
            m_sprite->position.setY(m_sprite->position.y() - speed);
            break;
        }
        case (Qt::Key_A) :
        {
            m_sprite->position.setX(m_sprite->position.x() - speed);
            break;
        }

        case (Qt::Key_D) :
        {
            m_sprite->position.setX(m_sprite->position.x() + speed);
            break;
        }

        case (Qt::Key_1) :
        {
            (qSharedPointerCast<CGFF::BatchRenderer2D>(Layer2D::getRenderer()))->setRenderTarget(CGFF::RenderTarget::SCREEN);
            break;
        }

        case (Qt::Key_2) :
        {
            (qSharedPointerCast<CGFF::BatchRenderer2D>(Layer2D::getRenderer()))->setRenderTarget(CGFF::RenderTarget::BUFFER);
            break;
        }

        case (Qt::Key_3) :
        {
            Layer2D::getRenderer()->setPostEffects(true);
            break;
        }

        case (Qt::Key_4) :
        {
            Layer2D::getRenderer()->setPostEffects(false);
            break;
        }
        }
    }

	void Test2DLayer::closeEvent(QCloseEvent *event)
	{
		Layer2D::closeEvent(event);
		m_sprite.clear();
		m_sprite2.clear();
		m_mask.clear();
	}

}
