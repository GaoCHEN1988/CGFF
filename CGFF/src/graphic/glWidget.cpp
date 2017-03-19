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

	m_tileLayer = QSharedPointer<CGFF::TileLayer>(new CGFF::TileLayer(m_shaderProgram, m_proj));

#ifdef TEST_50K
	for (float y = 0; y < 9.0f; y += 0.05)
	{
		for (float x = 0; x < 16.0f; x += 0.05)
		{
			m_tileLayer->add(
				QSharedPointer<CGFF::Renderable2D>(
					new CGFF::Sprite(x, y, 0.04f, 0.04f, QVector4D(rand() % 1000 / 1000.0f, 0, 1, 1))));
		}
	}
#else
	QMatrix4x4 mTrans;
	mTrans.translate(-2, -2, 0);
	QSharedPointer<CGFF::Group> group = QSharedPointer<CGFF::Group>(new CGFF::Group(mTrans));
	group->add(QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(0, 0, 3, 3, QVector4D(1, 1, 1, 1))));
	group->add(QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(0.2, 0.2, 2, 2, QVector4D(1, 0, 1, 1))));

	QMatrix4x4 mTrans2;
	mTrans2.translate(0.2, 0.2, 0);
	QSharedPointer<CGFF::Group> button = QSharedPointer<CGFF::Group>(new CGFF::Group(mTrans2));
	button->add(QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(0, 0, 1, 1, QVector4D(0.2f, 0.3f, 0.8f, 1))));

	group->add(qSharedPointerDynamicCast<CGFF::Renderable2D>(button));

	//m_tileLayer->add(QSharedPointer<CGFF::Renderable2D>(new CGFF::Sprite(-1.5, -1.5, 3, 3, QVector4D(1, 1, 1, 1))));
	m_tileLayer->add(QSharedPointer<CGFF::Renderable2D>(group));

#endif
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);

	m_world.setToIdentity();
	m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
	m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
	m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

	// Use our shader
	//glUseProgram(shaderProgram.programId());
	m_shaderProgram->bind(); //Equal to glUseProgram

	m_shaderProgram->setUniformValue(m_projMatrixLoc, m_proj);

	QMatrix4x4 m;
#ifdef TEST_50K
	m.translate(-8, -4.5, -4.0);
#else
	m.translate(0, 0, -8.0);
#endif

	m_shaderProgram->setUniformValue(m_mvMatrixLoc, m);
	m_shaderProgram->release();

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

