#include "sceneResource.h"
#include "resourceManager.h"

namespace CGFF
{
	SceneResource::SceneResource()
		: m_camera(nullptr)
		, m_entities()
		, m_lights()
		, m_skyBoxes()
        , m_environments()
	{}

	void SceneResource::addLight(const QString& name, const QSharedPointer<Light>& light)
	{
		auto lookup = m_lights.find(name);
		if (lookup == m_lights.end())
		{
			m_lights.insert(name, QSharedPointer<Light>(light));
		}
        else
        {
            //TO DO: use message box
            qWarning("Light with name is existed, use another name.");
        }
	}

	void SceneResource::addEntity(const QString& name, const QSharedPointer<Entity>& object)
	{
		auto lookup = m_entities.find(name);
		if (lookup == m_entities.end())
		{
			m_entities.insert(name, QSharedPointer<Entity>(object));
		}
		else
		{
			//TO DO: use message box
			qWarning("Object with name is existed, use another name.");
		}
	}

    void SceneResource::addModelObject(const QString& name, const QSharedPointer<ModelObject>& object)
    {
        auto lookup = m_modelObjects.find(name);
        if (lookup == m_modelObjects.end())
        {
            m_modelObjects.insert(name, QSharedPointer<ModelObject>(object));
        }
        else
        {
            //TO DO: use message box
            qWarning("Object with name is existed, use another name.");
        }
    }

	void SceneResource::addSkyBox(const QString& name, const QSharedPointer<Entity>& skybox, const QSharedPointer<Texture>& environment)
	{
		auto lookup = m_skyBoxes.find(name);
		if (lookup == m_skyBoxes.end())
		{
			m_skyBoxes.insert(name, skybox);
		}

        auto lookup2 = m_environments.find(name);
        if (lookup2 == m_environments.end())
        {
            m_environments.insert(name, environment);
        }
	}

	void SceneResource::changeEntityName(const QString& preName, const QString& newName)
	{
		if (preName == newName)
			return;

		auto lookup = m_entities.find(preName);
		if (lookup != m_entities.end())
		{
			m_entities[newName] = lookup.value();
			m_entities.remove(preName);
		}

        changeTransformAndUniformName(preName, newName);
	}

	void SceneResource::changeLightName(const QString& preName, const QString& newName)
	{
		if (preName == newName)
			return;

		auto lookup = m_lights.find(preName);
		if (lookup != m_lights.end())
		{
			m_lights[newName] = lookup.value();
			m_lights.remove(preName);
		}

        changeTransformAndUniformName(preName, newName);
	}

	void SceneResource::changeSkyBoxName(const QString& preName, const QString& newName)
	{
		if (preName == newName)
			return;

		auto lookup = m_skyBoxes.find(preName);
		if (lookup != m_skyBoxes.end())
		{
			m_skyBoxes[newName] = lookup.value();
			m_skyBoxes.remove(preName);
		}

        auto lookup2 = m_environments.find(preName);
        if (lookup2 != m_environments.end())
        {
            m_environments[newName] = lookup2.value();
            m_environments.remove(preName);
        }

        changeTransformAndUniformName(preName, newName);
	}

    void SceneResource::changeModelName(const QString& preName, const QString& newName)
    {
        if (preName == newName)
            return;

        auto lookup = m_modelObjects.find(preName);
        if (lookup != m_modelObjects.end())
        {
            m_modelObjects[newName] = lookup.value();
            m_modelObjects.remove(preName);
        }

        changeTransformAndUniformName(preName, newName);
    }

    void SceneResource::changeTransformAndUniformName(const QString& preName, const QString& newName)
    {
        if (preName == newName)
            return;

        auto lookup = ResourceManager::UiTransformMats.find(preName);
        if (lookup != ResourceManager::UiTransformMats.end())
        {
            ResourceManager::UiTransformMats[newName] = lookup.value();
            ResourceManager::UiTransformMats.remove(preName);
        }

        auto lookup2 = ResourceManager::UiTransformVecs.find(preName);
        if (lookup2 != ResourceManager::UiTransformVecs.end())
        {
            ResourceManager::UiTransformVecs[newName] = lookup2.value();
            ResourceManager::UiTransformVecs.remove(preName);
        }

        auto lookup3 = ResourceManager::UiUniformDatas.find(preName);
        if (lookup3 != ResourceManager::UiUniformDatas.end())
        {
            ResourceManager::UiUniformDatas[newName] = lookup3.value();
            ResourceManager::UiUniformDatas.remove(preName);
        }
    }

	QSharedPointer<Shader> SceneResource::getEntityShader(const QString& entityName)
	{
		auto lookup = m_entities.find(entityName);
		if (lookup != m_entities.end())
		{
			return lookup.value()->getComponent<MeshComponent>()->mesh->getMaterialInstance()->getMaterial()->getShader();
		}

		return nullptr;
	}

    void SceneResource::setEntityShader(const QString& entityName, const QSharedPointer<Shader>& shader)
    {
        auto lookup = m_entities.find(entityName);
        if (lookup != m_entities.end())
        {
            QSharedPointer<MaterialInstance> material = QSharedPointer<MaterialInstance>(
                new MaterialInstance(QSharedPointer<Material>(
                    new Material(shader))));
            lookup.value()->getComponent<MeshComponent>()->mesh->setMaterial(material);
        }
    }

    QSharedPointer<MaterialInstance> SceneResource::getEntityMaterialInstance(const QString& entityName)
    {
        auto lookup = m_entities.find(entityName);
        if (lookup != m_entities.end())
        {
            return lookup.value()->getComponent<MeshComponent>()->mesh->getMaterialInstance();
        }

        return nullptr;
    }

    void SceneResource::setEntityMaterialInstance(const QString& entityName, const QSharedPointer<MaterialInstance>& material)
    {
        auto lookup = m_entities.find(entityName);
        if (lookup != m_entities.end())
        {
            lookup.value()->getComponent<MeshComponent>()->mesh->setMaterial(material);
        }
    }

    bool SceneResource::isModelObjectExisted(const QString& modelName)
    {
        auto lookup = m_modelObjects.find(modelName);
        if (lookup != m_modelObjects.end())
            return true;
        else
            return false;
    }
}