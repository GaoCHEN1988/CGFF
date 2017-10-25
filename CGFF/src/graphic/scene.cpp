#include "scene.h"

namespace CGFF {

    Scene::Scene(QSize size)
		: m_camera(nullptr)
		, m_size(size)
        , m_lightSetup(nullptr)
        , m_skyBox(nullptr)
        , m_environment(nullptr)
    {
        QMatrix4x4 m;
        m.perspective(65.0f, float(m_size.width()) / float(m_size.height()), 0.1f, 1000.0f);
        m_camera = QSharedPointer<Camera>(new MayaCamera(m));
    }

    Scene::Scene(QSharedPointer<Camera>& camera)
        : m_camera(camera)
        , m_lightSetup(nullptr)
        , m_skyBox(nullptr)
        , m_environment(nullptr)
    {
    }

    Scene::~Scene()
    {
        m_entities.clear();
    }

    void Scene::add(const QSharedPointer<Entity>& entity)
    {
        m_entities.append(entity);
        if (!entity->getComponent<TransformComponent>())
        {
            qDebug("Entity does not have Transform Component, creating...");
            entity->addComponent(QSharedPointer<Component>(new TransformComponent(QMatrix4x4())));
        }
    }

    void Scene::add(const QSharedPointer<Light>& light)
    {
        if (m_lightSetup.isNull())
            m_lightSetup = QSharedPointer<LightSetup>(new LightSetup);

        m_lightSetup->add(light);
    }

    void Scene::pushLightSetup(QSharedPointer<LightSetup>& lightSetup)
    {
        m_lightSetupStack.append(lightSetup);
    }

    QSharedPointer<LightSetup> Scene::popLightSetup()
    {
        QSharedPointer<LightSetup> lightSetup = m_lightSetupStack.back();
        m_lightSetupStack.pop_back();
        return lightSetup;
    }

    void Scene::render(QSharedPointer<Renderer3D>& renderer)
    {
        m_camera->update();
        renderer->begin();
		renderer->beginScene(m_camera);

        if (!m_skyBox.isNull())
        {
            MeshComponent* mesh = m_skyBox->getComponent<MeshComponent>();
            if (mesh)
            {
                TransformComponent* tc = m_skyBox->getComponent<TransformComponent>();
                if (!tc)
                    qFatal("Mesh does not have transform!"); // Meshes MUST have transforms

                QMatrix4x4 vm = m_camera->getViewMatrix();
                mesh->mesh->getMaterialInstance()->setUniform("u_ViewMatrix", QMatrix4x4(QMatrix3x3(vm.toGenericMatrix<3, 3>())));
                renderer->submitMesh(mesh->mesh, tc->getTransform());
            }
        }

        if (!m_lightSetup.isNull())
        {
            renderer->submitLightSetup(m_lightSetup);
        }

        //for (uint i = 0; i < m_lightSetupStack.size(); i++)
        //    renderer->submitLightSetup(m_lightSetupStack[i]);

        for (QSharedPointer<Entity> entity : m_entities)
        {
            MeshComponent* mesh = entity->getComponent<MeshComponent>();
            if (mesh)
            {
                TransformComponent* tc = entity->getComponent<TransformComponent>();
                if(!tc)
                    qFatal("Mesh does not have transform!"); // Meshes MUST have transforms

                if(!m_environment.isNull())
                    mesh->mesh->getMaterialInstance()->setTexture("u_EnvironmentMap", m_environment);

                renderer->submitMesh(mesh->mesh, tc->getTransform());
            }
        }

		renderer->endScene();
        renderer->end();
    }

	void Scene::setCamera(const QSharedPointer<Camera>& camera)
	{
		m_camera = camera;
		m_camera->focus();
	}

    void Scene::setSkyBox(const QSharedPointer<Entity>& skyBox, const QSharedPointer<Texture>& environment)
    {
        m_environment = environment;
        m_skyBox = skyBox;
    }

	void Scene::close()
	{
		m_entities.clear();
		m_lightSetupStack.clear();
	}
}