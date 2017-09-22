#ifndef QTUI_RESOURCE_MODEL_H
#define QTUI_RESOURCE_MODEL_H

#include "resource/resourceManager.h"
#include "utils/types.h"

#include <QStandardItemModel>

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

		public slots:

		//void onEntityTranform(const QString& name);
	signals:
		void entityAdded(const QString& name);

	private:
		QStandardItem* m_itemScene;
		QStandardItem* m_itemEntity;
		QStandardItem* m_itemLight;
		QStandardItem* m_itemSkybox;
		static int m_cubeCount;
		static int m_planeCount;
		static int m_sphereCount;
	};
}

#endif
