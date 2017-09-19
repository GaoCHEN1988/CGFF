#ifndef CGFF_RESOURCE_UNIT_H
#define CGFF_RESOURCE_UNIT_H

#include "graphic/meshFactory.h"
#include "graphic/model.h"
#include "entity/entity.h"
#include "graphic/pbrMaterial.h"
#include "graphic/shader/shaderManager.h"
#include "graphic/light.h"

namespace CGFF
{
	class SceneResource
	{
	public:
		SceneResource()
			: m_camera(nullptr)
			, m_entities()
			, m_lights()
			, m_skyBox(nullptr)
		{}

		const QSharedPointer<Camera>& getCamera() const
		{
			return m_camera;
		}

		void setCamera(const QSharedPointer<Camera>& cam)
		{
			m_camera = cam;
		}

		const QMap<QString, QSharedPointer<Entity>>& getObjects() const
		{
			return m_entities;
		}

		void addObject(const QString& name, const QSharedPointer<Entity>& object)
		{
			auto lookup = m_entities.find(name);
			if (lookup == m_entities.end())
			{
				m_entities.insert(name, QSharedPointer<Entity>(object));
			}
		}

		const QMap<QString, QSharedPointer<Light>>& getLights() const
		{
			return m_lights;
		}

		void addLight(const QString& name, const QSharedPointer<Light>& light)
		{
			auto lookup = m_lights.find(name);
			if (lookup == m_lights.end())
			{
				m_lights.insert(name, QSharedPointer<Light>(light));
			}
		}

		const QSharedPointer<Material>& getSkyBox() const
		{
			return m_skyBox;
		}

		void addSkyBox(const QSharedPointer<Material>& skybox)
		{
			m_skyBox = skybox;
		}

	private:
		QSharedPointer<Camera> m_camera;
		QMap<QString, QSharedPointer<Entity>> m_entities;
		QMap<QString, QSharedPointer<Light>> m_lights;
		QSharedPointer<Material> m_skyBox;

	};
}

#endif