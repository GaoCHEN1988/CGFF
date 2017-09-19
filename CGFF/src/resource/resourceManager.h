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

	private:
		static QMap<QString, QSharedPointer<SceneResource>> m_sceneResources;
		static QMap<QString, QSharedPointer<Texture>> m_textureResources;

	};
}

#endif