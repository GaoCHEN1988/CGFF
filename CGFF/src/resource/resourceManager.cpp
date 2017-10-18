#include "resourceManager.h"

namespace CGFF {

	QMap<QString, QSharedPointer<SceneResource>> ResourceManager::m_sceneResources;

	QString ResourceManager::m_scene3DName = "Scene3D";
	QString ResourceManager::m_scene2DName = "Scene2D";

    QString ResourceManager::EntityHierarchyName = "Entities";
    QString ResourceManager::LightHierarchyName = "Lights";
    QString ResourceManager::SkyBoxHierarchyName = "SkyBox";
    QString ResourceManager::ModelHierarchyName = "Models";

	//QSharedPointer<SceneResource> ResourceManager::m_currentScene2D = nullptr;
	//QSharedPointer<SceneResource> ResourceManager::m_currentScene3D = nullptr;

	QMap<QString, TransformMat> ResourceManager::TransformMats;
	QMap<QString, TransformVec> ResourceManager::TransformVecs;

	QSharedPointer<SceneResource> ResourceManager::getSceneResource(const QString& name)
	{
		auto lookup = m_sceneResources.find(name);
		if (lookup != m_sceneResources.end())
		{
			//m_currentScene3D = lookup.value();
			return lookup.value();
		}
		else
		{
			m_sceneResources.insert(name, QSharedPointer<SceneResource>(new SceneResource));
			//m_currentScene3D = m_sceneResources[name];
			return m_sceneResources[name];
		}
	}

	void ResourceManager::removeSceneResource(const QString& name)
	{
		auto lookup = m_sceneResources.find(name);
		if (lookup != m_sceneResources.end())
		{
			m_sceneResources.remove(name);
		}
	}

   
    QSharedPointer<Entity> ResourceManager::getEntity(const QString& sceneName, const QString& entityName)
    {
        auto lookup = m_sceneResources.find(sceneName);
        if (lookup != m_sceneResources.end())
        {
            auto entityLookup = lookup.value()->getEntities().find(entityName);

            if (entityLookup != lookup.value()->getEntities().end())
            {
                return entityLookup.value();
            }

            return nullptr;
        }

        return nullptr;
    }

    QSharedPointer<Light> ResourceManager::getLight(const QString& sceneName, const QString& lightName)
    {
        auto lookup = m_sceneResources.find(sceneName);
        if (lookup != m_sceneResources.end())
        {
            auto lightLookup = lookup.value()->getLights().find(lightName);

            if (lightLookup != lookup.value()->getLights().end())
            {
                return lightLookup.value();
            }

            return nullptr;
        }

        return nullptr;
    }

    QSharedPointer<ModelObject> ResourceManager::getModelObject(const QString& sceneName, const QString& modelObjName)
    {
        auto lookup = m_sceneResources.find(sceneName);
        if (lookup != m_sceneResources.end())
        {
            auto lightLookup = lookup.value()->getModelObject().find(modelObjName);

            if (lightLookup != lookup.value()->getModelObject().end())
            {
                return lightLookup.value();
            }

            return nullptr;
        }

        return nullptr;
    }
}