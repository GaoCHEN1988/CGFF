#ifndef QTUI_RESOURCE_MODEL_H
#define QTUI_RESOURCE_MODEL_H

#include "resource/resourceManager.h"
#include "utils/types.h"

#include <QStandardItemModel>

namespace QTUI {

    struct EntityTransformMat
    {
        QMatrix4x4 translateMat;
        QMatrix4x4 rotateMat;
        QMatrix4x4 scaleMat;

        QMatrix4x4 getTransform()
        {
            return translateMat*rotateMat*scaleMat;
        }
    };

    struct EntityTransformVec
    {
        QVector3D translateVec;
        QVector3D rotateVec;
        QVector3D scaleVec;

        EntityTransformVec()
            : translateVec()
            , rotateVec()
            , scaleVec(1.0, 1.0, 1.0)
        {}
    };

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

		public slots:

		//void onEntityTranform(const QString& name);
        void onAddEntity(CGFF::EntityType type);
        void onSetCurrentEntity(const QString& name);
        void onSetCurrentLight(const QString& name);
        void onSetCurrentSkyBox(const QString& name);

	signals:
        void entityAdded(const QString& name);
        void currentEntitySet(const QString& name, const EntityTransformVec& transform);
        void currentLightSet(const QString& name, const EntityTransformVec& transform);
        void currentSkyBoxSet(const QString& name, const EntityTransformVec& transform);

	private:
		QStandardItem* m_itemScene;
		QStandardItem* m_itemEntity;
		QStandardItem* m_itemLight;
		QStandardItem* m_itemSkybox;
		static int m_cubeCount;
		static int m_planeCount;
		static int m_sphereCount;

        QString m_currentScene;
        QString m_currentEntity;
        QString m_currentLight;
        QString m_currentSkybox;

        QMap<QString, EntityTransformMat> m_entityTransformMats;
        QMap<QString, EntityTransformVec> m_entityTransformVecs;
	};
}

#endif
