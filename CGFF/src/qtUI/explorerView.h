#ifndef QTUI_EXPLORER_VIEW_H
#define QTUI_EXPLORER_VIEW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QPushButton>

namespace QTUI {

	class ExplorerView : public QWidget
	{
		Q_OBJECT

	public:

		ExplorerView(QWidget *parent = Q_NULLPTR);
		virtual ~ExplorerView() {};

		public slots:
		void onMkdir();
		void onRm();

	private:
		QFileSystemModel * m_fileModel;
		QTreeView * m_treeView;

		QPushButton * m_mkdirButton;
		QPushButton * m_rmButton;
	};
}

#endif