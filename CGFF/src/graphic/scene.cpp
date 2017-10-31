#include "scene.h"

namespace CGFF {

    Scene::Scene(QSize size, const QString& name)
		: m_camera(nullptr)
		, m_size(size)
        , m_name(name)
    {
        initSceneResource();
    }

    Scene::Scene(QSharedPointer<Camera>& camera, const QString& name)
        : m_camera(camera)
        , m_name(name)
    {
        initSceneResource();
    }

    Scene::~Scene()
    {
    }

    void Scene::add(const QString& name, const QSharedPointer<Entity>& entity)
    {
        m_resource->addEntity(name, entity);
    }

    void Scene::add(const QString& name, const QSharedPointer<Light>& light)
    {
        m_resource->addLight(name, light);
    }

    void Scene::render(QSharedPointer<Renderer3D>& renderer)
    {
        m_camera->update();
        renderer->begin();
		renderer->beginScene(m_camera);

        if (!m_resource->getCurrentSkyBox().isNull())
        {
            MeshComponent* mesh = m_resource->getCurrentSkyBox()->getComponent<MeshComponent>();
            if (mesh)
            {
                TransformComponent* tc = m_resource->getCurrentSkyBox()->getComponent<TransformComponent>();
                if (!tc)
                    qFatal("Mesh does not have transform!"); // Meshes MUST have transforms

                QMatrix4x4 vm = m_camera->getViewMatrix();
                mesh->mesh->getMaterialInstance()->setUniform("u_ViewMatrix", QMatrix4x4(QMatrix3x3(vm.toGenericMatrix<3, 3>())));
                renderer->submitMesh(mesh->mesh, tc->getTransform());
            }
        }

        if (!m_resource->getLights().isEmpty())
        {
            QSharedPointer<LightSetup> lightSetup = QSharedPointer<LightSetup>(new LightSetup);

            for (QSharedPointer<Light> light : m_resource->getLights())
            {
                lightSetup->add(*light);
            }

            renderer->submitLightSetup(lightSetup);
        }

        for (QSharedPointer<Entity> entity : m_resource->getEntities())
        {
            MeshComponent* mesh = entity->getComponent<MeshComponent>();
            if (mesh)
            {
                TransformComponent* tc = entity->getComponent<TransformComponent>();
                if(!tc)
                    qFatal("Mesh does not have transform!"); // Meshes MUST have transforms

                if(!m_resource->getCurrentEnvironment().isNull())
                    mesh->mesh->getMaterialInstance()->setTexture("u_EnvironmentMap", m_resource->getCurrentEnvironment());

                renderer->submitMesh(mesh->mesh, tc->getTransform());
            }
        }

		renderer->endScene();
        renderer->end();
    }

	void Scene::setCamera(const QSharedPointer<Camera>& camera)
	{
        m_resource->setCamera(camera);
        m_camera = m_resource->getCamera();
		m_camera->focus();
	}

	void Scene::close()
	{
	}

    void Scene::initSceneResource()
    {
        ResourceManager::CurrentSceneName = m_name;
        m_resource = ResourceManager::getSceneResource(m_name);

        QMatrix4x4 m;
        m.perspective(65.0f, float(m_size.width()) / float(m_size.height()), 0.1f, 1000.0f);
        m_resource->setCamera(QSharedPointer<Camera>(new MayaCamera(m)));
        m_camera = m_resource->getCamera();

    }
}