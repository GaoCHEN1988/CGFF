#ifndef QTUI_OBJECT_LIST_VIEW_H
#define QTUI_OBJECT_LIST_VIEW_H

#include "baseView.h"
#include <QWidget>
#include <QTreeView>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
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

        void onCustomContextMenu(const QPoint &point);

	private:
		void init();
        void setupConnections();
        bool isEditableItem(const QModelIndex &index);

	private:
		QTreeView * m_treeView;
        QLabel * m_check_shadow_label;
        QCheckBox * m_shadow_checkBox;
        QLabel * m_renderer_label;
        QComboBox * m_renderer_combobox;
	};

}
#endif