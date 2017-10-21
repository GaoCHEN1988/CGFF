#ifndef QTUI_RESOURCE_MODEL_H
#define QTUI_RESOURCE_MODEL_H

#include "utils/types.h"
#include "resource/resourceManager.h"
#include "resource/textureManager.h"

#include <QStandardItemModel>
#include <QSet>

namespace QTUI {

	class ResourceModel : public QStandardItemModel
	{
		Q_OBJECT
    public:
        enum class CurrentObjectType
        {
            NONE,
            ENTITY,
            LIGHT,
            MODEL
        };
	public:

		ResourceModel(QObject *parent = Q_NULLPTR);
		virtual ~ResourceModel() {};

		QString addCube();
		QString addPlane();
        QString addSphere();
		void addScene();

        void translateCurrentObject(const QVector3D& tanslate);
        void rotateCurrentObject(float angle, const QVector3D& rotate);
        void scaleCurrentObject(const QVector3D& scale);

		QString getShaderName(const QString& entityName);
        QVector<CGFF::UniformInfo> getShaderUniformsInfo(const QString& entityName);
        QVector<CGFF::ShaderResourceUniformInfo> getShaderResourcesInfo(const QString& entityName);

        template<typename T>
        void changeCurrentEntityUniformValue(const QString& uniformName, const T& data)
        {
            QSharedPointer<CGFF::MaterialInstance> materialInstance = CGFF::ResourceManager::getSceneResource(m_currentScene)->getEntityMaterialInstance(m_currentEntity);
            materialInstance->setUniform(uniformName, data);
            CGFF::ResourceManager::UiUniformDatas[m_currentEntity] = QSharedPointer<CGFF::UiUniformData<T>>(new CGFF::UiUniformData<T>(uniformName, data));
        }

        template<typename T>
        void changeCurrentEntityTextureUniform(const QString& textureUniform, const T& path)
        {
            qFatal("Texture path type not supported, must be QString ot QStringList!");
        }

        template<>
        void changeCurrentEntityTextureUniform(const QString& textureUniform, const QString& path)
        {
            QSharedPointer<CGFF::MaterialInstance> materialInstance = CGFF::ResourceManager::getSceneResource(m_currentScene)->getEntityMaterialInstance(m_currentEntity);
            materialInstance->setTexture(textureUniform, CGFF::TextureManager::getTexture2D(path));
            CGFF::ResourceManager::UiUniformDatas[m_currentEntity] = QSharedPointer<CGFF::UiUniformData<QString>>(new CGFF::UiUniformData<QString>(textureUniform, path));
        }

        template<>
        void changeCurrentEntityTextureUniform(const QString& textureUniform, const QStringList& path)
        {
            if (path.isEmpty())
                return;

            QSharedPointer<CGFF::MaterialInstance> materialInstance = CGFF::ResourceManager::getSceneResource(m_currentScene)->getEntityMaterialInstance(m_currentEntity);
            materialInstance->setTexture(textureUniform, CGFF::TextureManager::getTextureCube(path));
            CGFF::ResourceManager::UiUniformDatas[m_currentEntity] = QSharedPointer<CGFF::UiUniformData<QString>>(new CGFF::UiUniformData<QString>(textureUniform, path[0]));
        }

		public slots:

		//void onEntityTranform(const QString& name);
        void onAddEntity(CGFF::EntityType type);
        void onLoadModel(const QString& path);
        void onSetCurrentEntity(const QString& name);
        void onSetCurrentLight(const QString& name);
        void onSetCurrentSkyBox(const QString& name);
        void onSetCurrentModel(const QString& name);
        void onItemChanged(QStandardItem *item);
        void onSetEmptyItem();
		void onShaderUniformChanged(const QString& name, const CGFF::UniformType& type);
		void onShaderResourceChanged(const QString& name, const CGFF::ShaderResourceType& type);

	signals:
        void entityAdded(const QString& name);
        void modelObjectAdded(const QString& name);
        void currentEntitySet(const QString& name, const CGFF::UiTransformVec& transform);
        void currentLightSet(const QString& name, const CGFF::UiTransformVec& transform);
        void currentSkyBoxSet(const QString& name, const CGFF::UiTransformVec& transform);
        void currentModelObjectSet(const QString& name, const CGFF::UiTransformVec& transform);
        void currentItemNameChanged(const QString& name);
        void setEmptyItem();

	private:
		void setupConnections();
		bool addNameInSet(const QString& name, QSet<QString>& set);
		QString changeNameInSet(const QString& preName, const QString& newName, QSet<QString>& set);

        void translateCurrentEntity(const QVector3D& tanslate);
        void rotateCurrentEntity(float angle, const QVector3D& rotate);
        void scaleCurrentEntity(const QVector3D& scale);

        void translateCurrentModelObject(const QVector3D& tanslate);
        void rotateCurrentModelObject(float angle, const QVector3D& rotate);
        void scaleCurrentModelObject(const QVector3D& scale);

	private:
		QStandardItem* m_itemScene;
		QStandardItem* m_itemEntity;
		QStandardItem* m_itemLight;
        QStandardItem* m_itemSkybox;
        QStandardItem* m_itemModel;

        QString m_currentScene;
        QString m_currentEntity;
        QString m_currentLight;
        QString m_currentSkybox;
        QString m_currentModel;

		QSet<QString> m_sceneNames;
		QSet<QString> m_entityNames;
		QSet<QString> m_lightNames;
		QSet<QString> m_skyboxNames;
        QSet<QString> m_shaderNames;
        QSet<QString> m_modelObjectNames;
        //QMap<QString, UiTransformMat> m_entityTransformMats;
        //QMap<QString, UiTransformVec> m_entityTransformVecs;

        CurrentObjectType m_currentObjType;

		static int m_cubeCount;
		static int m_planeCount;
        static int m_sphereCount;
        //static QMap<QString, int> m_modelCounts;
	};
}

#endif
