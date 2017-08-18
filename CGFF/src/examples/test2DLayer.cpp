#include "test2DLayer.h"
#include "graphic/shader/shaderFactory.h"
namespace CGFF {

    Test2DLayer::Test2DLayer(QSize size)
        : Layer2D(QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D(size)))
        , m_size(size)
    {
    }

    void Test2DLayer::init() 
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::SCREEN);
        
        //QSharedPointer<QOpenGLShaderProgram> pfShader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);
        //bool success = pfShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shaders/postfx.vert");
        //// load and compile fragment shader
        //success = pfShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shaders/postfx.frag");
        //Layer2D::getRenderer()->addPostEffectsPass(QSharedPointer<CGFF::PostEffectsPass>(new CGFF::PostEffectsPass(pfShader, m_size)));
        //Layer2D::getRenderer()->setPostEffects(false);
    
        m_sprite = QSharedPointer<CGFF::Sprite>(new CGFF::Sprite(0.0f, 0.0f, 100, 100, Texture2D::createFromFile("Resources/tb.png")));

        Layer2D::add(m_sprite);
        m_mask = QSharedPointer<CGFF::Mask>(new CGFF::Mask(Texture2D::createFromFile("Resources/mask.png")));
        //Layer2D::setMask(m_mask);

        m_fpsLabel = QSharedPointer<CGFF::Label>(new CGFF::Label("fps", 10, m_size.height() - 50, 150, 32, QVector4D(1, 1, 1, 1)));
        Layer2D::add(m_fpsLabel);
        
        m_time.start();
        last_count = 0;
        m_frameCount = 0;
    }

    void Test2DLayer::render() 
    {
        Layer2D::render();

        // FPS count
        ++m_frameCount;
        int elapsed = m_time.elapsed();
        if (elapsed >= 1000)
        {
            last_count = m_frameCount;
            m_frameCount = 0;
            m_time.restart();
        }

        m_fpsLabel->setText(QString::number(last_count));
    }

    void Test2DLayer::resize(int width, int height) 
    {
        Layer2D::resize(width, height);
    }
    void Test2DLayer::mousePressEvent(QMouseEvent *event) {}
    void Test2DLayer::mouseMoveEvent(QMouseEvent *event) {}
    void Test2DLayer::mouseReleaseEvent(QMouseEvent *event) {}
    void Test2DLayer::keyPressEvent(QKeyEvent *event) 
    {
        float speed = 8.0f;
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
}
