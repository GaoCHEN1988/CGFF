#ifndef QTUI_OBJECT_LIST_VIEW_H
#define QTUI_OBJECT_LIST_VIEW_H

#include "baseView.h"
#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

namespace QTUI {

	class ObjectListView : public BaseView
	{
		Q_OBJECT

	public:

		ObjectListView(QWidget *parent = Q_NULLPTR);
		virtual ~ObjectListView() {};

		void setModel(ResourceModel * model) override;

		public slots:
		void onAddEntity(CGFF::EntityType type);

	signals:
		void entityAdded(const QString& name);

	private:
		void init();

	private:
		QTreeView * m_treeView;
	};

}
#endif