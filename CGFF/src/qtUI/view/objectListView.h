#ifndef QTUI_OBJECT_LIST_VIEW_H
#define QTUI_OBJECT_LIST_VIEW_H

#include "qtUI/model/resourceModel.h"

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

namespace QTUI {

	class ObjectListView : public QWidget
	{
		Q_OBJECT

	public:

		ObjectListView(QWidget *parent = Q_NULLPTR);
		virtual ~ObjectListView() {};

		public slots:

		void onAddEntity(CGFF::EntityType type);

	signals:
		void entityAdded(const QString& name);

	private:
		void init();

	private:
		QTreeView * m_treeView;
		ResourceModel * m_model;
	};

}
#endif