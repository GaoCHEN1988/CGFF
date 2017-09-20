#include "app3DLayer.h"
#include "resource/resourceManager.h"
#include "graphic/shader/shaderFactory.h"

namespace CGFF
{
	App3DLayer::App3DLayer(QSize size, QWidget *parent) 
		: Layer3D(QSharedPointer<Scene>(new Scene(size))
			, QSharedPointer<ForwardRenderer>(new ForwardRenderer(size))
			, parent)
		, m_camera(nullptr)
		, m_entities()
		, m_lights(nullptr)
		, m_skyboxMaterial(nullptr)
	{
	}

	App3DLayer::~App3DLayer()
	{
	}


	void App3DLayer::init()
	{
		loadFromResource();

		//QSharedPointer<LightSetup> lights = QSharedPointer<LightSetup>(new LightSetup());
		//lights->add(QSharedPointer<Light>(new Light(QVector3D(0.8f, 0.8f, 0.8f))));
		//m_scene->pushLightSetup(lights);

		//QSharedPointer<Entity> cube = QSharedPointer<Entity>(
		//	new Entity(MeshFactory::CreateDebugCube(5, QVector4D(0.6, 0.6, 0.6, 1.0),
		//		QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(ShaderFactory::DebugShader())))))));
		//m_scene->add(cube);
	}

	void App3DLayer::render(QSharedPointer<Renderer3D>& renderer)
	{
		// Remove the translation part for skybox
        if (m_skyboxMaterial)
        {
            QMatrix4x4 vm = m_scene->getCamera()->getViewMatrix();
            m_skyboxMaterial->setUniform("u_ViewMatrix", QMatrix4x4(QMatrix3x3(vm.toGenericMatrix<3, 3>())));
        }
	}

	void App3DLayer::mousePressEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mousePressEvent(event);
	}

	void App3DLayer::mouseMoveEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mouseMoveEvent(event);
	}

	void App3DLayer::mouseReleaseEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mousePressEvent(event);
	}

	void App3DLayer::closeEvent(QCloseEvent *event)
	{
	}

	void App3DLayer::loadFromResource()
	{
		foreach(QSharedPointer<Entity> entity, ResourceManger::getSceneResource("Scene1")->getObjects())
		{
			m_scene->add(entity);
		}

		QSharedPointer<LightSetup> lights = QSharedPointer<LightSetup>(new LightSetup());

		foreach(QSharedPointer<Light> light, ResourceManger::getSceneResource("Scene1")->getLights())
		{
			lights->add(light);
		}

		m_scene->pushLightSetup(lights);
	}
}