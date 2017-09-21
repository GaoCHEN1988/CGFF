#include "resourceManager.h"
#include "graphic/api/texture2D.h"
#include "graphic/api/textureCube.h"
#include "graphic/api/textureDepth.h"

namespace CGFF {

	QMap<QString, QSharedPointer<SceneResource>> ResourceManger::m_sceneResources;
	QMap<QString, QSharedPointer<Texture>> ResourceManger::m_textureResources;

	QString ResourceManger::m_scene3DName = "Scene3D";
	QString ResourceManger::m_scene2DName = "Scene2D";

	QSharedPointer<SceneResource> ResourceManger::m_currentScene2D = nullptr;
	QSharedPointer<SceneResource> ResourceManger::m_currentScene3D = nullptr;

	QSharedPointer<SceneResource> ResourceManger::getSceneResource(const QString& name)
	{
		auto lookup = m_sceneResources.find(name);
		if (lookup != m_sceneResources.end())
		{
			m_currentScene3D = lookup.value();
			return lookup.value();
		}
		else
		{
			m_sceneResources.insert(name, QSharedPointer<SceneResource>(new SceneResource));
			m_currentScene3D = m_sceneResources[name];
			return m_sceneResources[name];
		}
	}

	void ResourceManger::removeSceneResource(const QString& name)
	{
		auto lookup = m_sceneResources.find(name);
		if (lookup != m_sceneResources.end())
		{
			m_sceneResources.remove(name);
		}
	}

	QSharedPointer<Texture> ResourceManger::getTexture2D(const QString& path)
	{
		auto lookup = m_textureResources.find(path);
		if (lookup != m_textureResources.end())
		{
			return lookup.value();
		}
		else
		{
			m_textureResources.insert(path, Texture2D::createFromFile(path));
			return m_textureResources[path];
		}
	}

	void ResourceManger::removeTexture2D(const QString& path)
	{
		auto lookup = m_textureResources.find(path);
		if (lookup != m_textureResources.end())
		{
			m_textureResources.remove(path);
		}
	}
}