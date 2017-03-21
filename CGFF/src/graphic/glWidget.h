#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QSharedPointer>
#include <QOpenGLTexture>

#include "../maths/qtmaths.h"
#include "buffer/buffer.h"
#include "buffer/indexBuffer.h"
#include "buffer/vertexArray.h"
#include "renderable2d.h"
#include "simple2Drenderer.h"
#include "batchRenderer2d.h"
#include "sprite.h"
#include "staticSprite.h"
#include "layer/tileLayer.h"
#include "layer/group.h"

#define TEST_50K

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

	public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int width, int height) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
	QSharedPointer<QOpenGLShaderProgram> m_shaderProgram;
	GLuint vertexPosition_modelspaceID;
	//GLuint vertexbuffer;
	GLuint color_location;
	//GLuint colorbuffer;

	QMatrix4x4 m_proj;
	QMatrix4x4 m_camera;
	QMatrix4x4 m_world;
	GLuint m_xRot;
	GLuint m_yRot;
	GLuint m_zRot;
	GLuint m_projMatrixLoc;
	GLuint m_mvMatrixLoc;
	QPoint m_lastPos;

	//QSharedPointer<CGFF::StaticSprite> m_renderable2d;
	//QSharedPointer<CGFF::Renderable2D> m_sprite;
	//QSharedPointer<CGFF::Simple2DRenderer> m_simpleRenderer;
	QSharedPointer<CGFF::BatchRenderer2D> m_batch;

	//std::vector<QSharedPointer<CGFF::Renderable2D>> sprites;
	QSharedPointer<QOpenGLTexture> m_texture;
	QSharedPointer<CGFF::TileLayer> m_tileLayer;
	QSharedPointer<CGFF::Group> m_group;
};

#endif