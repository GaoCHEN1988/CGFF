#include "glWidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <iostream>
GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
    //QSurfaceFormat qFormat = QOpenGLWidget::format();
    //QOpenGLContext* context = new QOpenGLContext(this);
#ifdef OPENGL_ES

#else
    ////QSurfaceFormat qFormat;
    //qFormat.setProfile(QSurfaceFormat::CoreProfile);
    //qFormat.setVersion(4, 4);
    //QOpenGLContext::currentContext()->setFormat(qFormat);

#endif

    setFocusPolicy(Qt::ClickFocus);
}

GLWidget::~GLWidget()
{
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_xRot) {
		m_xRot = angle;
		emit xRotationChanged(angle);
		update();
	}
}

void GLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot) {
		m_yRot = angle;
		emit yRotationChanged(angle);
		update();
	}
}

void GLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot) {
		m_zRot = angle;
		emit zRotationChanged(angle);
		update();
	}
}

void GLWidget::initializeGL()
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

#ifdef TEST_50K
	m_vTextures.push_back(QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QImage("src/graphic/shader/particle.png").mirrored())));
	m_vTextures.push_back(QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QImage("src/graphic/shader/tb.png").mirrored())));
	m_vTextures.push_back(QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QImage("src/graphic/shader/tc.png").mirrored())));
#endif

	m_shaderProgram->bind();
	m_shaderProgram->setUniformValue("projMatrix", m_proj);

	GLuint programID = m_shaderProgram->programId();

	m_camera.setToIdentity();
	m_camera.translate(0, 0, -1);

	//m_tileLayer = QSharedPointer<CGFF::TileLayer>(new CGFF::TileLayer(m_shaderProgram, m_proj));
    m_layer = QSharedPointer<CGFF::Layer>(new CGFF::Layer(QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D(this->size())),
        m_shaderProgram, m_proj));
    
	m_shaderProgram->release();

#ifdef TEST_50K

	//for (float y = 0; y < 9.0f; y += 0.4)
	//{
	//	for (float x = 0; x < 16.0f; x += 0.4)
	//	{
	//		m_tileLayer->add(
	//			QSharedPointer<CGFF::Renderable2D>(
	//				new CGFF::Sprite(x, y, 0.39f, 0.39f, QVector4D(rand() % 1000 / 1000.0f, 0, 1, 1))));
	//	}
	//}

	for (float y = 0; y < 9.0f; y += 0.2)
	{
		for (float x = 0; x < 16.0f; x += 0.2)
		{
			m_tileLayer->add(
				QSharedPointer<CGFF::Renderable2D>(
					new CGFF::Sprite(x, y, 0.19f, 0.19f, m_vTextures[rand() % 3])));
		}
	}


#else
	//QMatrix4x4 mTrans;
	//mTrans.translate(-2, -2, 0);
	//QSharedPointer<CGFF::Group> group = QSharedPointer<CGFF::Group>(new CGFF::Group(mTrans));
	//group->add(QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(0, 0, 3, 3, QVector4D(1, 1, 1, 1))));
	//group->add(QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(0.2, 0.2, 2, 2, QVector4D(1, 0, 1, 1))));
	//QMatrix4x4 mTrans2;
	//mTrans2.translate(0.2, 0.2, 0.1);
	//QSharedPointer<CGFF::Group> button = QSharedPointer<CGFF::Group>(new CGFF::Group(mTrans2));
	//button->add(QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(0, 0, 1, 1, QVector4D(0.2f, 0.3f, 0.8f, 1))));

	//group->add(qSharedPointerDynamicCast<CGFF::Renderable2D>(button));

	//m_tileLayer->add(QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(-1.5, -1.5, 3, 3, QVector4D(1, 1, 1, 1))));
	//m_tileLayer->add(QSharedPointer<CGFF::Renderable2D>(group));

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

#endif

    CGFF::GL->glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
    m_time.start();
    last_count = 0;
    m_frameCount = 0;
}

void GLWidget::paintGL()
{
    CGFF::GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//CGFF::GL->glEnable(GL_DEPTH_TEST);
    CGFF::GL->glEnable(GL_BLEND);
    CGFF::GL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_world.setToIdentity();
	m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
	m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
	m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

	//// Use our shader
	m_shaderProgram->bind(); //Equal to glUseProgram
	m_shaderProgram->setUniformValue("projMatrix", m_proj);
	QMatrix4x4 m;
#ifdef TEST_50K
	m.translate(-8, -4.5, -4.0);
#else
	m.translate(0, 0, -8.0);
#endif

	m_shaderProgram->setUniformValue("mvMatrix", m);

	m_shaderProgram->release();

	//m_tileLayer->render();
    m_layer->render();

	GLenum error = CGFF::GL->glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OPENGL Error:" << error << std::endl;

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

void GLWidget::resizeGL(int width, int height)
{
    CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	m_proj.setToIdentity();
	m_proj.perspective(45.0f, GLfloat(width) / height, 0.01f, 100.0f);
    (qSharedPointerCast<CGFF::BatchRenderer2D>(m_layer->getRenderer()))->setViewportSize(QSize((GLsizei)width, (GLsizei)height));
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(m_xRot + 8 * dy);
		setYRotation(m_yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(m_xRot + 8 * dy);
		setZRotation(m_zRot + 8 * dx);
	}
	m_lastPos = event->pos();
}


void GLWidget::keyPressEvent(QKeyEvent *event)
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