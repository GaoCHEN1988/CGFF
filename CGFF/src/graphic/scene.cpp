#include "scene.h"

namespace CGFF {

    Scene::Scene(QSize size)
		: m_camera(nullptr)
		, m_size(size)
    {
        QMatrix4x4 m;
        m.perspective(65.0f, float(m_size.width()) / float(m_size.height()), 0.1f, 1000.0f);
        m_camera = QSharedPointer<Camera>(new MayaCamera(m));
    }

    Scene::Scene(QSharedPointer<Camera>& camera)
        : m_camera(camera)
    {
    }

    Scene::~Scene()
    {
        m_entities.clear();
    }

    void Scene::add(QSharedPointer<Entity>& entity)
    {
        m_entities.append(entity);
        if (!entity->getComponent<TransformComponent>())
        {
            qDebug("Entity does not have Transform Component, creating...");
            entity->addComponent(QSharedPointer<Component>(new TransformComponent(QMatrix4x4())));
        }
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

        for (uint i = 0; i < m_lightSetupStack.size(); i++)
            renderer->submitLightSetup(m_lightSetupStack[i]);

        for (QSharedPointer<Entity> entity : m_entities)
        {
            MeshComponent* mesh = entity->getComponent<MeshComponent>();
            if (mesh)
            {
                TransformComponent* tc = entity->getComponent<TransformComponent>();
                if(!tc)
                    qFatal("Mesh does not have transform!"); // Meshes MUST have transforms
                renderer->submitMesh(mesh->mesh, tc->transform);
            }
        }

		renderer->endScene();
        renderer->end();
    }

	void Scene::setCamera(QSharedPointer<Camera> camera)
	{
		m_camera = camera;
		m_camera->focus();
	}

	void Scene::close()
	{
		m_entities.clear();
		m_lightSetupStack.clear();
	}
}