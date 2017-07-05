#include "test2DLayer.h"
#include "graphic/shaderFactory/shaderFasctory.h"
namespace CGFF {

    Test2DLayer::Test2DLayer(QSize size)
        : Layer2D(QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D(size)),DefaultShader(), m_proj)
        , m_size(size)
    {
    }

    void Test2DLayer::init() 
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::BUFFER);
        
        QSharedPointer<QOpenGLShaderProgram> pfShader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);
        bool success = pfShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader/postfx.vert");
        // load and compile fragment shader
        success = pfShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader/postfx.frag");
        Layer2D::getRenderer()->addPostEffectsPass(QSharedPointer<CGFF::PostEffectsPass>(new CGFF::PostEffectsPass(pfShader, m_size)));
        Layer2D::getRenderer()->setPostEffects(false);
    
        m_sprite = QSharedPointer<CGFF::Sprite>(new CGFF::Sprite(0.0f, 0.0f, 2, 2,
            QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QImage("Resources/tb.png").mirrored()))));

        Layer2D::add(m_sprite);
        QSharedPointer<QOpenGLTexture> tempTexture = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QImage("Resources/mask.png")));
        tempTexture->setWrapMode(QOpenGLTexture::ClampToBorder);
        m_mask = QSharedPointer<CGFF::Mask>(new CGFF::Mask(tempTexture));
        //Layer2D::setMask(m_mask);

        m_fpsLabel = QSharedPointer<CGFF::Label>(new CGFF::Label("fps", -4, 2, QVector4D(1, 1, 1, 1)));
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

        m_fpsLabel->setText(QString::number(last_count).toStdString());
    }

    void Test2DLayer::resize(int width, int height) 
    {
        CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        Layer2D::resize(width, height);
        (qSharedPointerCast<CGFF::BatchRenderer2D>(Layer2D::getRenderer()))->setViewportSize(QSize((GLsizei)width, (GLsizei)height));
    }
    void Test2DLayer::mousePressEvent(QMouseEvent *event) {}
    void Test2DLayer::mouseMoveEvent(QMouseEvent *event) {}
    void Test2DLayer::mouseReleaseEvent(QMouseEvent *event) {}
    void Test2DLayer::keyPressEvent(QKeyEvent *event) 
    {
        float speed = 0.5f;
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
