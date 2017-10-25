#ifndef CGFF_RESOURCE_UNIT_H
#define CGFF_RESOURCE_UNIT_H

#include "graphic/meshFactory.h"
#include "graphic/model.h"
#include "entity/entity.h"
#include "entity/modelObject.h"
#include "graphic/pbrMaterial.h"
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

		inline const QMap<QString, QSharedPointer<Entity>>& getEntities() const
		{
			return m_entities;
		}

		inline const QMap<QString, QSharedPointer<Light>>& getLights() const
		{
			return m_lights;
		}

        inline const QMap<QString, QSharedPointer<Texture>>& getEnvironments() const
        {
            return m_environments;
        }
        inline const QMap<QString, QSharedPointer<Entity>>& getSkyBox() const
		{
			return m_skyBoxes;
		}

        inline const QMap<QString, QSharedPointer<ModelObject>>& getModelObject() const
        {
            return m_modelObjects;
        }

		void addLight(const QString& name, const QSharedPointer<Light>& light);

        void addEntity(const QString& name, const QSharedPointer<Entity>& object);

        void addModelObject(const QString& name, const QSharedPointer<ModelObject>& object);

		void addSkyBox(const QString& name, const QSharedPointer<Entity>& skybox, const QSharedPointer<Texture>& environment);

		void changeEntityName(const QString& preName, const QString& newName);

		void changeLightName(const QString& preName, const QString& newName);

        void changeSkyBoxName(const QString& preName, const QString& newName);

        void changeModelName(const QString& preName, const QString& newName);

        void changeTransformAndUniformName(const QString& preName, const QString& newName);

        QSharedPointer<Shader> getEntityShader(const QString& entityName);

        void setEntityShader(const QString& entityName, const QSharedPointer<Shader>& shader);

        QSharedPointer<MaterialInstance> getEntityMaterialInstance(const QString& entityName);

        void setEntityMaterialInstance(const QString& entityName, const QSharedPointer<MaterialInstance>& material);

        bool isModelObjectExisted(const QString& modelName);

	private:
		QSharedPointer<Camera> m_camera;
        QMap<QString, QSharedPointer<Entity>> m_entities;
        QMap<QString, QSharedPointer<ModelObject>> m_modelObjects;
		QMap<QString, QSharedPointer<Light>> m_lights;
        QMap<QString, QSharedPointer<Entity>> m_skyBoxes;
        QMap<QString, QSharedPointer<Texture>> m_environments;
	};
}

#endif