#ifndef CGFF_RESOURCE_MANAGER_H
#define CGFF_RESOURCE_MANAGER_H

#include "sceneResource.h"

namespace CGFF {

	class ResourceManager
	{
	public:
		ResourceManager() = delete;

		//Scene resource
		static QSharedPointer<SceneResource> getSceneResource(const QString& name);
		static void removeSceneResource(const QString& name);

		static QString getScene3DName() 
		{
			return m_scene3DName;
		}

		static QString getScene2DName()
		{
			return m_scene2DName;
		}

        static QString getEntityHierarchyName()
        {
            return m_entityHierarchyName;
        }

        static QString getLightHierarchyName()
        {
            return m_lightHierarchyName;
        }

        static QString getSkyBoxHierarchyName()
        {
            return m_skyBoxHierarchyName;
        }

        static QSharedPointer<Entity> getEntity(const QString& sceneName, const QString& entityName);
        static QSharedPointer<Light> getLight(const QString& sceneName, const QString& lightName);

	private:
		static QMap<QString, QSharedPointer<SceneResource>> m_sceneResources;

		static QString m_scene3DName;
		static QString m_scene2DName;

        static QString m_entityHierarchyName;
        static QString m_lightHierarchyName;
        static QString m_skyBoxHierarchyName;

		//static QSharedPointer<SceneResource> m_currentScene2D;
		//static QSharedPointer<SceneResource> m_currentScene3D;

	};
}

#endif