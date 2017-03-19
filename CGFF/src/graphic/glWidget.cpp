#include "glWidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <iostream>
GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{

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
	// initialize OpenGL
	initializeOpenGLFunctions();

	m_shaderProgram = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);
	// load and compile vertex shader
	bool success;
	success = m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader/SimpleVertexShader.vert");
	// load and compile fragment shader
	success = m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader/SimpleFragmentShader.frag");
	m_shaderProgram->link();

	GLuint programID = m_shaderProgram->programId();

	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	m_projMatrixLoc = glGetUniformLocation(programID, "projMatrix");
	m_mvMatrixLoc = glGetUniformLocation(programID, "mvMatrix");
	color_location = glGetAttribLocation(programID, "v_color");
	m_camera.setToIdentity();
	m_camera.translate(0, 0, -1);

	//m_renderable2d = QSharedPointer<CGFF::StaticSprite>(new CGFF::StaticSprite(0,0,0.5, 0.5, QVector4D(1.0, 0, 0, 1.0), shaderProgram));
	//m_simpleRenderer = QSharedPointer<CGFF::Simple2DRenderer>(new CGFF::Simple2DRenderer());
	//
	//m_sprite = QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(0.0, 0.0, 1, 1, QVector4D(1.0, 0, 0, 1.0)));

	//for (float y = 0; y < 9.0f; y += 0.05)
	//{
	//	for (float x = 0; x < 16.0f; x += 0.05)
	//	{
	//		sprites.push_back(
	//			QSharedPointer<CGFF::Renderable2D>(
	//				new CGFF::Sprite(x, y, 0.04f, 0.04f, QVector4D(rand() % 1000 / 1000.0f, 0, 1, 1))));
	//	}
	//}

	m_tileLayer = QSharedPointer<CGFF::TileLayer>(new CGFF::TileLayer(m_shaderProgram, m_proj));
	for (float y = 0; y < 9.0f; y += 0.05)
	{
		for (float x = 0; x < 16.0f; x += 0.05)
		{
			m_tileLayer->add(
				QSharedPointer<CGFF::Renderable2D>(
					new CGFF::Sprite(x, y, 0.04f, 0.04f, QVector4D(rand() % 1000 / 1000.0f, 0, 1, 1))));
		}
	}
	//m_batch = QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	m_world.setToIdentity();
	m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
	m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
	m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

	// Use our shader
	//glUseProgram(shaderProgram.programId());
	m_shaderProgram->bind(); //Equal to glUseProgram

	m_shaderProgram->setUniformValue(m_projMatrixLoc, m_proj);

	QMatrix4x4 m;
	m.translate(-8, -4.5, -4.0);

	m_shaderProgram->setUniformValue(m_mvMatrixLoc, m);
	m_shaderProgram->release();

	//m_batch->begin();
	////m_batch->submit(m_sprite);
	//for (int i = 0; i < sprites.size(); i++)
	//{
	//	m_batch->submit(sprites[i]);
	//}
	//m_batch->end();
	//m_batch->flush();

	m_tileLayer->render();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OPENGL Error:" << error << std::endl;


}

void GLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	m_proj.setToIdentity();
	m_proj.perspective(45.0f, GLfloat(width) / height, 0.01f, 100.0f);
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

