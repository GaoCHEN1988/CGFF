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

		ResourceModel(QObject *parent = Q_NULLPTR);
		virtual ~ResourceModel() {};

		QString addCube();
		QString addPlane();
		QString addSphere();
		void addScene();
        void translateCurrentEntity(const QVector3D& tanslate);
        void rotateCurrentEntity(float angle, const QVector3D& rotate);
        void scaleCurrentEntity(const QVector3D& scale);

		QString getShaderName(const QString& entityName);
		QList<CGFF::UniformInfo> getShaderUniforms(const QString& entityName);
		QList<CGFF::ShaderResourceUniformInfo> getShaderResources(const QString& entityName);

		public slots:

		//void onEntityTranform(const QString& name);
        void onAddEntity(CGFF::EntityType type);
        void onSetCurrentEntity(const QString& name);
        void onSetCurrentLight(const QString& name);
        void onSetCurrentSkyBox(const QString& name);
		void onItemChanged(QStandardItem *item);

	signals:
        void entityAdded(const QString& name);
        void currentEntitySet(const QString& name, const CGFF::EntityTransformVec& transform);
        void currentLightSet(const QString& name, const CGFF::EntityTransformVec& transform);
        void currentSkyBoxSet(const QString& name, const CGFF::EntityTransformVec& transform);
		void currentItemNameChanged(const QString& name);

	private:
		void setupConnections();
		bool addNameInSet(const QString& name, QSet<QString>& set);
		QString changeNameInSet(const QString& preName, const QString& newName, QSet<QString>& set);


	private:
		QStandardItem* m_itemScene;
		QStandardItem* m_itemEntity;
		QStandardItem* m_itemLight;
		QStandardItem* m_itemSkybox;

        QString m_currentScene;
        QString m_currentEntity;
        QString m_currentLight;
        QString m_currentSkybox;

		QSet<QString> m_sceneNames;
		QSet<QString> m_entityNames;
		QSet<QString> m_lightNames;
		QSet<QString> m_skyboxNames;
		QSet<QString> m_shaderNames;
        //QMap<QString, EntityTransformMat> m_entityTransformMats;
        //QMap<QString, EntityTransformVec> m_entityTransformVecs;

		static int m_cubeCount;
		static int m_planeCount;
		static int m_sphereCount;

		static QVector4D m_defaultColor;
	};
}

#endif
