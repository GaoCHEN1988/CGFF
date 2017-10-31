#ifndef QTUI_RESOURCE_MODEL_H
#define QTUI_RESOURCE_MODEL_H

#include "utils/types.h"
#include "resource/resourceManager.h"
#include "resource/textureManager.h"

#include <QStandardItemModel>
#include <QSet>

namespace QTUI {
    enum class CurrentObjectType
    {
        NONE,
        ENTITY,
        LIGHT,
        MODEL,
        SKYBOX
    };

	class ResourceModel : public QStandardItemModel
	{
		Q_OBJECT
	public:

		ResourceModel(QObject *parent = Q_NULLPTR);
		virtual ~ResourceModel() {};

        void translateCurrentObject(const QVector3D& tanslate);
        void rotateCurrentObject(float angle, const QVector3D& rotate);
        void scaleCurrentObject(const QVector3D& scale);

		QString getShaderName(const QString& entityName);
        QVector<CGFF::UniformInfo> getShaderUniformsInfo(const QString& entityName);
        QVector<CGFF::ShaderResourceUniformInfo> getShaderResourcesInfo(const QString& entityName);

        QString getModelShaderName(const QString& modelName);
        QVector<CGFF::UniformInfo> getModelShaderUniformsInfo(const QString& modelName);
        QVector<CGFF::ShaderResourceUniformInfo> getModelShaderResourcesInfo(const QString& modelName);

        template<typename T>
        void changeCurrentEntityUniformValue(const QString& uniformName, const T& data)
        {
            QSharedPointer<CGFF::MaterialInstance> materialInstance = CGFF::ResourceManager::getSceneResource(m_currentScene)->getEntityMaterialInstance(m_currentEntity);
            materialInstance->setUniform(uniformName, data);
            CGFF::ResourceManager::UiUniformDatas[m_currentEntity][uniformName] = QSharedPointer<CGFF::UiUniformData<T>>(new CGFF::UiUniformData<T>(uniformName, data));
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
            CGFF::ResourceManager::UiUniformDatas[m_currentEntity][textureUniform] = QSharedPointer<CGFF::UiUniformData<QString>>(new CGFF::UiUniformData<QString>(textureUniform, path));
        }

        template<>
        void changeCurrentEntityTextureUniform(const QString& textureUniform, const QStringList& path)
        {
            if (path.isEmpty())
                return;

            QSharedPointer<CGFF::MaterialInstance> materialInstance = CGFF::ResourceManager::getSceneResource(m_currentScene)->getEntityMaterialInstance(m_currentEntity);
            materialInstance->setTexture(textureUniform, CGFF::TextureManager::getTextureCube(path));
            CGFF::ResourceManager::UiUniformDatas[m_currentEntity][textureUniform] = QSharedPointer<CGFF::UiUniformData<QString>>(new CGFF::UiUniformData<QString>(textureUniform, path[0]));
        }

        template<typename T>
        void changeCurrentModelUniformValue(const QString& uniformName, const T& data)
        {
            auto model = CGFF::ResourceManager::getSceneResource(m_currentScene)->getModelObject()[m_currentModel];
            auto modelEntities = model->getEntities();
            CGFF::ResourceManager::UiUniformDatas[m_currentModel][uniformName] = QSharedPointer<CGFF::UiUniformData<T>>(new CGFF::UiUniformData<T>(uniformName, data));

            for (const QString& entity_name : modelEntities.keys())
            {
                auto materialInstance = modelEntities[entity_name]->getComponent<CGFF::MeshComponent>()->mesh->getMaterialInstance();
                materialInstance->setUniform(uniformName, data);
                CGFF::ResourceManager::UiUniformDatas[entity_name][uniformName] = QSharedPointer<CGFF::UiUniformData<T>>(new CGFF::UiUniformData<T>(uniformName, data));
            }
        }

        template<typename T>
        void changeCurrentModelTextureUniform(const QString& textureUniform, const T& path)
        {
            qFatal("Texture path type not supported, must be QString ot QStringList!");
        }

        template<>
        void changeCurrentModelTextureUniform(const QString& textureUniform, const QString& path)
        {
            auto model = CGFF::ResourceManager::getSceneResource(m_currentScene)->getModelObject()[m_currentModel];
            auto modelEntities = model->getEntities();
            CGFF::ResourceManager::UiUniformDatas[m_currentModel][textureUniform] = QSharedPointer<CGFF::UiUniformData<QString>>(new CGFF::UiUniformData<QString>(textureUniform, path));
            for (const QString& entity_name : modelEntities.keys())
            {
                auto materialInstance = modelEntities[entity_name]->getComponent<CGFF::MeshComponent>()->mesh->getMaterialInstance();
                materialInstance->setTexture(textureUniform, CGFF::TextureManager::getTexture2D(path));
                CGFF::ResourceManager::UiUniformDatas[entity_name][textureUniform] = QSharedPointer<CGFF::UiUniformData<QString>>(new CGFF::UiUniformData<QString>(textureUniform, path));
            }
        }

        template<>
        void changeCurrentModelTextureUniform(const QString& textureUniform, const QStringList& path)
        {
            if (path.isEmpty())
                return;

            auto model = CGFF::ResourceManager::getSceneResource(m_currentScene)->getModelObject()[m_currentModel];
            auto modelEntities = model->getEntities();
            CGFF::ResourceManager::UiUniformDatas[m_currentModel][textureUniform] = QSharedPointer<CGFF::UiUniformData<QString>>(new CGFF::UiUniformData<QString>(textureUniform, path[0]));
            for (const QString& entity_name : modelEntities.keys())
            {
                auto materialInstance = modelEntities[entity_name]->getComponent<CGFF::MeshComponent>()->mesh->getMaterialInstance();
                materialInstance->setTexture(textureUniform, CGFF::TextureManager::getTextureCube(path));
                CGFF::ResourceManager::UiUniformDatas[entity_name][textureUniform] = QSharedPointer<CGFF::UiUniformData<QString>>(new CGFF::UiUniformData<QString>(textureUniform, path[0]));
            }
        }

		public slots:

        void onAddScene(const QString& name);
        void onAddEntity(CGFF::EntityType type);
        void onLoadModel(const QString& path);
        void onAddLight(const CGFF::LightType& type);
        void onLoadSkyBox(const QStringList& images);

        void onItemChanged(QStandardItem *item);
        void onCurrentSelectChanged(const QModelIndex &index);
        void onDeleteItem(const QModelIndex &index);
        void onSetCurrentEntityShader(const QString& shaderName);
        void onSetCurrentModelShader(const QString& shaderName);

	signals:

        void currentEntitySet(const QString& name, const CGFF::UiTransformVec& transform, const CGFF::UiUniformDataMap& uniformMap);
        void currentLightSet(const QString& name, const CGFF::UiTransformVec& transform, const CGFF::UiUniformDataMap& uniformMap);
        void currentSkyBoxSet(const QString& name);
        void currentModelObjectSet(const QString& name, const CGFF::UiTransformVec& transform, const CGFF::UiUniformDataMap& uniformMap);
        void currentItemNameChanged(const QString& name);
        void setEmptyItem();

	private:
		void setupConnections();
		bool addNameInSet(const QString& name, QSet<QString>& set);
		QString changeNameInSet(const QString& preName, const QString& newName, QSet<QString>& set);

        QString addCube();
        QString addPlane();
        QString addSphere();
        void addDirectionalLight();

        void translateCurrentEntity(const QVector3D& tanslate);
        void rotateCurrentEntity(float angle, const QVector3D& rotate);
        void scaleCurrentEntity(const QVector3D& scale);

        void translateCurrentModelObject(const QVector3D& tanslate);
        void rotateCurrentModelObject(float angle, const QVector3D& rotate);
        void scaleCurrentModelObject(const QVector3D& scale);

        void translateCurrentLight(const QVector3D& tanslate);

        void setCurrentEntity(const QString& name);
        void setCurrentLight(const QString& name);
        void setCurrentSkyBox(const QString& name);
        void setCurrentModel(const QString& name);

        void deleteEntity(const QString& name, int row);
        void deleteLight(const QString& name, int row);
        void deleteSkybox(const QString& name, int row);
        void deleteModel(const QString& name, int row);

        QModelIndex getTopParent(QModelIndex itemIndex);


	private:
        QMap<QString, QStandardItem*> m_sceneItems;
        QMap<QString, QStandardItem*> m_entityItems;
        QMap<QString, QStandardItem*> m_lightItems;
        QMap<QString, QStandardItem*> m_skyboxItems;
        QMap<QString, QStandardItem*> m_modelObjectItems;

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

        CurrentObjectType m_currentObjType;

		static int m_cubeCount;
		static int m_planeCount;
        static int m_sphereCount;
        static int m_lightCount;
        static int m_skyBoxCount;
	};
}

#endif
