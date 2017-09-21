#ifndef CGFF_RESOURCE_MANAGER_H
#define CGFF_RESOURCE_MANAGER_H

#include "sceneResource.h"
#include "graphic/api/texture.h"

namespace CGFF {

	class ResourceManger
	{
	public:
		ResourceManger() = delete;

		//Scene resource
		static QSharedPointer<SceneResource> getSceneResource(const QString& name);
		static void removeSceneResource(const QString& name);

		//Texture resource
		static QSharedPointer<Texture> getTexture2D(const QString& path);
		static void removeTexture2D(const QString& path);

		static QString getScene3DName() 
		{
			return m_scene3DName;
		}

		static QString getScene2DName()
		{
			return m_scene2DName;
		}

	private:
		static QMap<QString, QSharedPointer<SceneResource>> m_sceneResources;
		static QMap<QString, QSharedPointer<Texture>> m_textureResources;

		static QString m_scene3DName;
		static QString m_scene2DName;

		static QSharedPointer<SceneResource> m_currentScene2D;
		static QSharedPointer<SceneResource> m_currentScene3D;

	};
}

#endif