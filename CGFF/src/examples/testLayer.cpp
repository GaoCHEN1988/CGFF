#include "examples/testLayer.h"
#include <QKeyEvent>

TestLayer::TestLayer(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
}

void TestLayer::initializeGL()
{
#ifdef OPENGL_ES
#else
    QSurfaceFormat qFormat = QOpenGLWidget::format();
    qFormat.setProfile(QSurfaceFormat::CoreProfile);
    qFormat.setVersion(4, 4);
    QOpenGLContext::currentContext()->setFormat(qFormat);
#endif

    // initialize OpenGL
    CGFF::GL = QOpenGLContext::currentContext()->functions();
    CGFF::GL->initializeOpenGLFunctions();

    m_shaderProgram = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);

    bool success;

#ifdef OPENGL_ES
    // load and compile vertex shader
    success = m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader_es/SimpleVertexShader.vert");
    // load and compile fragment shader
    success = m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader_es/SimpleFragmentShader.frag");
#else
    // load and compile vertex shader
    success = m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader/SimpleVertexShader.vert");
    // load and compile fragment shader
    success = m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader/SimpleFragmentShader.frag");
#endif

    m_shaderProgram->link();

    m_shaderProgram->bind();
    m_shaderProgram->setUniformValue("projMatrix", m_proj);
    m_model.translate(0, 0, -8.0);

    m_shaderProgram->setUniformValue("mvMatrix", m_model);
    m_shaderProgram->release();

    m_layer = QSharedPointer<CGFF::Layer>(new CGFF::Layer(QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D(this->size())),
        m_shaderProgram, m_proj));

    m_layer->getRenderer()->setRenderTarget(CGFF::RenderTarget::BUFFER);
    QSharedPointer<QOpenGLShaderProgram> pfShader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);
    success = pfShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader/postfx.vert");
    // load and compile fragment shader
    success = pfShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader/postfx.frag");
    m_layer->getRenderer()->addPostEffectsPass(QSharedPointer<CGFF::PostEffectsPass>(new CGFF::PostEffectsPass(pfShader, this->size())));
    m_layer->getRenderer()->setPostEffects(false);

    m_sprite = QSharedPointer<CGFF::Sprite>(new CGFF::Sprite(0.0f, 0.0f, 2, 2,
        QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QImage("Resources/tb.png").mirrored()))));

    m_layer->add(m_sprite);
    QSharedPointer<QOpenGLTexture> tempTexture = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QImage("Resources/mask.png")));
    tempTexture->setWrapMode(QOpenGLTexture::ClampToBorder);
    m_mask = QSharedPointer<CGFF::Mask>(new CGFF::Mask(tempTexture));
    //m_layer->setMask(m_mask);

    m_fpsLabel = QSharedPointer<CGFF::Label>(new CGFF::Label("Test", -4, 2, QVector4D(1, 1, 1, 1)));
    m_layer->add(m_fpsLabel);

    CGFF::GL->glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
    m_time.start();
    last_count = 0;
    m_frameCount = 0;
}
void TestLayer::paintGL()
{
    CGFF::GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CGFF::GL->glEnable(GL_BLEND);
    CGFF::GL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //// Use our shader
    m_shaderProgram->bind(); //Equal to glUseProgram
    m_shaderProgram->setUniformValue("projMatrix", m_proj);
    m_shaderProgram->setUniformValue("mvMatrix", m_model);
    m_shaderProgram->release();

    //m_tileLayer->render();
    m_layer->render();

    GLenum error = CGFF::GL->glGetError();
    if (error != GL_NO_ERROR)
    {
        //To do: show error in logging system
    }

    // FPS count
    ++m_frameCount;
    int elapsed = m_time.elapsed();
    if (elapsed >= 1000)
    {
        /*
        TO DO: Show FPS
        */
        last_count = m_frameCount;
        m_frameCount = 0;
        m_time.restart();
    }

    m_fpsLabel->setText(QString::number(last_count).toStdString());
}

void TestLayer::resizeGL(int width, int height)
{
    CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(width) / height, 0.01f, 100.0f);
    (qSharedPointerCast<CGFF::BatchRenderer2D>(m_layer->getRenderer()))->setViewportSize(QSize((GLsizei)width, (GLsizei)height));
}

void TestLayer::mousePressEvent(QMouseEvent *event)
{

}

void TestLayer::mouseMoveEvent(QMouseEvent *event)
{
}
void TestLayer::keyPressEvent(QKeyEvent *event)
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
        (qSharedPointerCast<CGFF::BatchRenderer2D>(m_layer->getRenderer()))->setRenderTarget(CGFF::RenderTarget::SCREEN);
        break;
    }

    case (Qt::Key_2) :
    {
        (qSharedPointerCast<CGFF::BatchRenderer2D>(m_layer->getRenderer()))->setRenderTarget(CGFF::RenderTarget::BUFFER);
        break;
    }

    case (Qt::Key_3) :
    {
        m_layer->getRenderer()->setPostEffects(true);
        break;
    }

    case (Qt::Key_4) :
    {
        m_layer->getRenderer()->setPostEffects(false);
        break;
    }
    }
    update();
}
