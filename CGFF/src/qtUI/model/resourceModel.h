#ifndef QTUI_RESOURCE_MODEL_H
#define QTUI_RESOURCE_MODEL_H

#include "resource/resourceManager.h"
#include "utils/types.h"

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
		QList<CGFF::UniformInfo> getShaderUniforms(const QString& entityName);
		QList<CGFF::ShaderResourceUniformInfo> getShaderResources(const QString& entityName);

        template<typename T>
        void changeCurrentEntityUniformValue(const QString& uniformName, const T& data)
        {
            QSharedPointer<CGFF::MaterialInstance> materialInstance = CGFF::ResourceManager::getSceneResource(m_currentScene)->getEntityMaterialInstance(m_currentEntity);
            materialInstance->setUniform(uniformName, data);
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
		void onShaderUniformChanged(const QString& name, const CGFF::UniformType& type);
		void onShaderResourceChanged(const QString& name, const CGFF::ShaderResourceType& type);

	signals:
        void entityAdded(const QString& name);
        void modelObjectAdded(const QString& name);
        void currentEntitySet(const QString& name, const CGFF::TransformVec& transform);
        void currentLightSet(const QString& name, const CGFF::TransformVec& transform);
        void currentSkyBoxSet(const QString& name, const CGFF::TransformVec& transform);
        void currentModelObjectSet(const QString& name, const CGFF::TransformVec& transform);
		void currentItemNameChanged(const QString& name);

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
        //QMap<QString, TransformMat> m_entityTransformMats;
        //QMap<QString, TransformVec> m_entityTransformVecs;

        CurrentObjectType m_currentObjType;

		static int m_cubeCount;
		static int m_planeCount;
		static int m_sphereCount;
	};
}

#endif
