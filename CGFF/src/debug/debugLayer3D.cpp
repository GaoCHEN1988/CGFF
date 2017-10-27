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
		m_debugMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(m_debugShader))));
	}

	void DebugLayer3D::init()
	{
		QSharedPointer<Material> lineMaterial = QSharedPointer<Material>(new Material(m_debugShader));

		QSharedPointer<MaterialInstance> lineInstance = QSharedPointer<MaterialInstance>(new MaterialInstance(lineMaterial));

		m_lineX = QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateLine(
				QVector3D(0,0,0), 
				QVector3D(20,0,0), 
				QVector4D(1.0, 0.0, 0.0, 1.0),  
				lineInstance)));

		m_lineY = QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateLine(
			QVector3D(0, 0, 0),
			QVector3D(0, 20, 0),
			QVector4D(0.0, 1.0, 0.0, 1.0),
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

        //m_scene->add(QSharedPointer<Light>(new Light(QVector3D(0.8f, 0.8f, 0.8f))));
		//ResourceManager::getSceneResource(ResourceManager::getScene3DName())->addLight("Light1", QSharedPointer<Light>(new Light(QVector3D(0.8f, 0.8f, 0.8f))));
	}

	void DebugLayer3D::render(QSharedPointer<Renderer3D>& renderer)
	{
		//GLenum error = CGFF::GL->glGetError();
		//if (error != GL_NO_ERROR)
		//{
		//	//To do: show error in logging system
		//	qFatal("Opengl error!");
		//}
	}

	void DebugLayer3D::tick()
	{
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

	void DebugLayer3D::addEntity(const QString& name)
	{
		addEntity(ResourceManager::getSceneResource(ResourceManager::getScene3DName())->getEntities()[name]);
	}

    void DebugLayer3D::addModelObject(const QString& name)
    {
        QSharedPointer<ModelObject> modelobj = ResourceManager::getSceneResource(ResourceManager::getScene3DName())->getModelObject()[name];

        for (const QString& key : modelobj->getEntities().keys())
        {
            addEntity(modelobj->getEntities()[key]);
        }
    }

    void DebugLayer3D::addLight(const QString& name)
    {
        m_scene->add(ResourceManager::getSceneResource(ResourceManager::getScene3DName())->getLights()[name]);
    }

    void DebugLayer3D::setSkyBox(const QString& name)
    {
        m_scene->setSkyBox(ResourceManager::getSceneResource(ResourceManager::getScene3DName())->getSkyBox()[name],
            ResourceManager::getSceneResource(ResourceManager::getScene3DName())->getEnvironments()[name]);
    }
}