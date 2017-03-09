#include "glWidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <iostream>
GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
	, m_sprite1(nullptr)
	, m_sprite2(nullptr)
	, m_ibo(nullptr)
{

}

GLWidget::~GLWidget()
{


#ifdef TEST
	if (m_sprite1) {
		m_sprite1->unbind();
		delete m_sprite1;
	}

	if (m_sprite2) {
		m_sprite2->unbind();
		delete m_sprite2;
	}

	if (m_ibo) {
		m_ibo->unbind();
		delete m_ibo;
	}
#else

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);

#endif
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

static const GLfloat g_vertex_buffer_data[] = {
	0.0f, 0.707f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
};

static const GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

void GLWidget::initializeGL()
{
	double a = 1.0 / 3;
	// initialize OpenGL
	initializeOpenGLFunctions();

	// load and compile vertex shader
	bool success;
	success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader/SimpleVertexShader.vert");
	// load and compile fragment shader
	success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader/SimpleFragmentShader.frag");
	shaderProgram.link();

	GLuint programID = shaderProgram.programId();

	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	m_projMatrixLoc = glGetUniformLocation(programID, "projMatrix");
	m_mvMatrixLoc = glGetUniformLocation(programID, "mvMatrix");
	color_location = glGetAttribLocation(programID, "v_color");
	m_camera.setToIdentity();
	m_camera.translate(0, 0, -1);

#ifdef  TEST

	GLfloat vertices[] =
	{
		-0.5, -0.5, 0,
		-0.5, 0.5, 0,
		0.5, 0.5, 0,
		0.5, -0.5, 0
	};

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLfloat colors1[] =
	{
		1.0, 0, 0, 1.0,
		1.0, 0, 0, 1.0,
		1.0, 0, 0, 1.0,
		1.0, 0, 0, 1.0
	};

	GLfloat colors2[] =
	{
		1.0, 0, 0, 1.0,
		0, 1.0, 0, 1.0,
		0, 0, 1.0, 1.0,
		1.0, 1.0, 0, 1.0
	};

	

	m_sprite1 = new CGFF::VertexArray(this);
	m_sprite2 = new CGFF::VertexArray(this);

	m_sprite1->addBuffer(new CGFF::Buffer(this, vertices, 4 * 3, 3), vertexPosition_modelspaceID);
	m_sprite1->addBuffer(new CGFF::Buffer(this, colors1, 4 * 4, 4), color_location);

	m_sprite2->addBuffer(new CGFF::Buffer(this, vertices, 4 * 3, 3), vertexPosition_modelspaceID);
	m_sprite2->addBuffer(new CGFF::Buffer(this, colors2, 4 * 4, 4), color_location);

	m_ibo = new CGFF::IndexBuffer(this, indices, 6);

#else
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		vertexPosition_modelspaceID, // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		color_location, // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
#endif

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

	shaderProgram.bind();

	// Use our shader
	glUseProgram(shaderProgram.programId());

	shaderProgram.setUniformValue(m_projMatrixLoc, m_proj);
	

#ifdef  TEST
	m_sprite1->bind();
	m_ibo->bind();
	QMatrix4x4 m = m_camera * m_world;
	m.translate(0.0, 0.0, 0.3);
	shaderProgram.setUniformValue(m_mvMatrixLoc, m);
	glDrawElements(GL_TRIANGLES, m_ibo->getCount(), GL_UNSIGNED_INT, 0);
	m_sprite1->unbind();
	m_ibo->unbind();

	m_sprite2->bind();
	m_ibo->bind();
	shaderProgram.setUniformValue(m_mvMatrixLoc, m_camera * m_world);
	glDrawElements(GL_TRIANGLES, m_ibo->getCount(), GL_UNSIGNED_INT, 0);
	m_sprite2->unbind();
	m_ibo->unbind();


#else
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

#endif

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OPENGL Error:" << error << std::endl;

	shaderProgram.release();

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

