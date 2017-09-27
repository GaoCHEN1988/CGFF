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
		SceneResource();

		inline const QSharedPointer<Camera>& getCamera() const
		{
			return m_camera;
		}

		inline void setCamera(const QSharedPointer<Camera>& cam)
		{
			m_camera = cam;
		}

		inline const QMap<QString, QSharedPointer<Entity>>& getObjects() const
		{
			return m_entities;
		}

		inline const QMap<QString, QSharedPointer<Light>>& getLights() const
		{
			return m_lights;
		}

		inline const QMap<QString, QSharedPointer<Material>>& getSkyBox() const
		{
			return m_skyBoxes;
		}

		void addLight(const QString& name, const QSharedPointer<Light>& light);

		void addObject(const QString& name, const QSharedPointer<Entity>& object);

		void addSkyBox(const QString& name, const QSharedPointer<Material>& skybox);

		void changeObjectName(const QString& preName, const QString& newName);

		void changeLightName(const QString& preName, const QString& newName);

		void changeSkyBoxName(const QString& preName, const QString& newName);

		QSharedPointer<Shader> getEntityShader(const QString& entityName);

	private:
		QSharedPointer<Camera> m_camera;
		QMap<QString, QSharedPointer<Entity>> m_entities;
		QMap<QString, QSharedPointer<Light>> m_lights;
		QMap<QString, QSharedPointer<Material>> m_skyBoxes;
	};
}

#endif