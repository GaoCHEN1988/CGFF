#include "debugLayer3D.h"
#include "graphic/shader/shaderFactory.h"
#include "graphic/meshFactory.h"
#include "resource/resourceManager.h"

namespace CGFF {

	DebugLayer3D::DebugLayer3D(const QSize& size, QWidget *parent)
		: Layer3D(QSharedPointer<CGFF::Scene>(new CGFF::Scene(size)), QSharedPointer<ForwardRenderer>(new ForwardRenderer(size)), parent)
		, m_mayaCamera(nullptr)
		, m_debugShader(nullptr)
		, m_lineX(nullptr)
		, m_lineY(nullptr)
		, m_lineZ(nullptr)
	{
		m_debugShader = ShaderFactory::DebugShader();
		m_debugMaterial = QSharedPointer<Material>(new Material(m_debugShader));
	}

	void DebugLayer3D::init()
	{
		QSharedPointer<Material> lineMaterial = QSharedPointer<Material>(new Material(m_debugShader));

		QSharedPointer<MaterialInstance> lineInstance = QSharedPointer<MaterialInstance>(new MaterialInstance(lineMaterial));

		m_lineX = QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateLine(
				QVector3D(0,0,0), 
				QVector3D(20,0,0), 
				QVector4D(0.0, 1.0, 0.0, 1.0),  
				lineInstance)));

		m_lineY = QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateLine(
			QVector3D(0, 0, 0),
			QVector3D(0, 20, 0),
			QVector4D(1.0, 0.0, 0.0, 1.0),
			lineInstance)));

		m_lineZ = QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateLine(
			QVector3D(0, 0, 0),
			QVector3D(0, 0, 20),
			QVector4D(0.0, 0.0, 1.0, 1.0),
			lineInstance)));

		m_scene->add(m_lineX);
		m_scene->add(m_lineY);
		m_scene->add(m_lineZ);
	}

	void DebugLayer3D::render(QSharedPointer<Renderer3D>& renderer)
	{
		QVector3D cameraPosition = m_scene->getCamera()->getPosition();
		m_debugMaterial->setUniform("viewPos", cameraPosition);

		GLenum error = CGFF::GL->glGetError();
		if (error != GL_NO_ERROR)
		{
			//To do: show error in logging system
			qFatal("Opengl error!");
		}
	}

	void DebugLayer3D::tick()
	{
	}

	void DebugLayer3D::resizeEvent(QResizeEvent *event)
	{
		Layer3D::resizeEvent(event);
		Layer3D::getScene()->getCamera()->resize(event->size().width(), event->size().height());
	}

	void DebugLayer3D::closeEvent(QCloseEvent *event)
	{
		m_lineX.clear();
		m_lineY.clear();
		m_lineZ.clear();
	}

	void DebugLayer3D::mousePressEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mousePressEvent(event);
	}

	void DebugLayer3D::mouseMoveEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mouseMoveEvent(event);
	}

	void DebugLayer3D::mouseReleaseEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mousePressEvent(event);
	}

	void DebugLayer3D::addEntity(const QSharedPointer<CGFF::Entity>& entity)
	{
		m_scene->add(entity);
	}

	void DebugLayer3D::addCube()
	{
		QSharedPointer<Entity> cube = QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateDebugCube(5, QVector4D(0.6,0.6,0.6,1.0),
				QSharedPointer<MaterialInstance>(new MaterialInstance(m_debugMaterial)))));

		addEntity(cube);
	}

	void DebugLayer3D::addPlane()
	{
		QSharedPointer<Entity> plane = QSharedPointer<Entity>(new Entity(MeshFactory::CreateDebugPlane(64, 64, QVector3D(0, 1, 0), QVector4D(0.6, 0.6, 0.6, 1.0), QSharedPointer<MaterialInstance>(new MaterialInstance(m_debugMaterial)))));
	
		addEntity(plane);
	}

	void DebugLayer3D::addSphere()
	{
		//QSharedPointer<Material> sphereMaterial = QSharedPointer<Material>(new Material(m_debugShader));

	}
}