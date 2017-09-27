#include "sceneResource.h"

namespace CGFF
{
	SceneResource::SceneResource()
		: m_camera(nullptr)
		, m_entities()
		, m_lights()
		, m_skyBoxes()
	{}

	void SceneResource::addLight(const QString& name, const QSharedPointer<Light>& light)
	{
		auto lookup = m_lights.find(name);
		if (lookup == m_lights.end())
		{
			m_lights.insert(name, QSharedPointer<Light>(light));
		}
	}

	void SceneResource::addObject(const QString& name, const QSharedPointer<Entity>& object)
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

	void SceneResource::addSkyBox(const QString& name, const QSharedPointer<Material>& skybox)
	{
		auto lookup = m_skyBoxes.find(name);
		if (lookup == m_skyBoxes.end())
		{
			m_skyBoxes.insert(name, QSharedPointer<Material>(skybox));;
		}
	}

	void SceneResource::changeObjectName(const QString& preName, const QString& newName)
	{
		if (preName == newName)
			return;

		auto lookup = m_entities.find(preName);
		if (lookup != m_entities.end())
		{
			m_entities[newName] = lookup.value();
			m_entities.remove(preName);
		}
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
}