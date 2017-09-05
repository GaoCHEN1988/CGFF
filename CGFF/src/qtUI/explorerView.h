#ifndef QTUI_EXPLORER_VIEW_H
#define QTUI_EXPLORER_VIEW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QPushButton>
#include <QTabWidget>

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
		void init();
		void mountDirectory(const QString& path, const QString& name);
		void mountDirs();

	private:
		//QFileSystemModel *	m_fileModel;
		//QTreeView *			m_treeView;
		QMap<int, QTreeView*> m_treeViews;
		QMap<int, QFileSystemModel*> m_fileModels;
		QTabWidget *		m_tabWidget;
		QPushButton *		m_mkdirButton;
		QPushButton *		m_rmButton;
	};
}

#endif