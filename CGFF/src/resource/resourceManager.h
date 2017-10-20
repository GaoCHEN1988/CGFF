#ifndef CGFF_RESOURCE_MANAGER_H
#define CGFF_RESOURCE_MANAGER_H

#include "sceneResource.h"

namespace CGFF {

    //Transform matrix to store transform data of material view
	struct UiTransformMat
	{
		QMatrix4x4 translateMat;
		QMatrix4x4 rotateMat;
		QMatrix4x4 scaleMat;

		QMatrix4x4 getTransform()
		{
			return translateMat*rotateMat*scaleMat;
		}
	};

    //Transform vectors to store transform data of material view
	struct UiTransformVec
	{
		QVector3D translateVec;
		QVector3D rotateVec;
		QVector3D scaleVec;

		UiTransformVec()
			: translateVec()
			, rotateVec()
			, scaleVec(1.0, 1.0, 1.0)
		{}
	};

    //To store uniform data of material view
    struct UiUniformDataInterface
    {

    };

    template <typename T>
    struct UiUniformData : public UiUniformDataInterface
    {
        QString uniformName;
        T data;

        UiUniformData<T>(const QString& name, const T& d)
            : uniformName(name)
            , data(d)
        {}
    };

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

        static QSharedPointer<Entity> getEntity(const QString& sceneName, const QString& entityName);
        static QSharedPointer<Light> getLight(const QString& sceneName, const QString& lightName);
        static QSharedPointer<ModelObject> getModelObject(const QString& sceneName, const QString& modelObjName);
        static bool isModelObjectExisted(const QString& modelObjName);
	public:
		static QMap<QString, UiTransformMat> UiTransformMats;
        static QMap<QString, UiTransformVec> UiTransformVecs;
        static QMap<QString, QSharedPointer<UiUniformDataInterface>> UiUniformDatas;

    public:
		static QMap<QString, QSharedPointer<SceneResource>> m_sceneResources;

		static QString m_scene3DName;
		static QString m_scene2DName;

        static QString EntityHierarchyName;
        static QString LightHierarchyName;
        static QString SkyBoxHierarchyName;
        static QString ModelHierarchyName;
		//static QSharedPointer<SceneResource> m_currentScene2D;
		//static QSharedPointer<SceneResource> m_currentScene3D;

	};
}

#endif