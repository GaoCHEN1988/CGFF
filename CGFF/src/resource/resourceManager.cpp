#include "resourceManager.h"

namespace CGFF {

	QMap<QString, QSharedPointer<SceneResource>> ResourceManager::m_sceneResources;

	QString ResourceManager::CurrentSceneName = "Scene";

    QString ResourceManager::EntityHierarchyName = "Entities";
    QString ResourceManager::LightHierarchyName = "Lights";
    QString ResourceManager::SkyBoxHierarchyName = "SkyBox";
    QString ResourceManager::ModelHierarchyName = "Models";

	QMap<QString, UiTransformMat> ResourceManager::UiTransformMats;
	QMap<QString, UiTransformVec> ResourceManager::UiTransformVecs;
    QMap<QString, UiUniformDataMap> ResourceManager::UiUniformDatas;

	QSharedPointer<SceneResource> ResourceManager::getSceneResource(const QString& name)
	{
		auto lookup = m_sceneResources.find(name);
		if (lookup != m_sceneResources.end())
		{
			return lookup.value();
		}
		else
		{
			m_sceneResources.insert(name, QSharedPointer<SceneResource>(new SceneResource));
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

    bool ResourceManager::isModelObjectExisted(const QString& modelObjName)
    {
        for (auto sceneResource: m_sceneResources)
        {
            if (sceneResource->isModelObjectExisted(modelObjName))
                return true;
        }

        return false;
    }

    QSharedPointer<Texture> ResourceManager::getEnvironment(const QString& sceneName, const QString& name)
    {
        auto lookup = m_sceneResources.find(sceneName);
        if (lookup != m_sceneResources.end())
        {
            auto envLookup = lookup.value()->getEnvironments().find(name);

            if (envLookup != lookup.value()->getEnvironments().end())
            {
                return envLookup.value();
            }

            return nullptr;
        }

        return nullptr;
    }
}