#ifndef CGFF_MAINWINDOW_H
#define CGFF_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
//#include "application/applicationWindow.h"
#include "application/debugWindow.h"
#include "application/appWindow.h"
#include "qtUI/explorerView.h"
#include "qtUI/view/objectInfoView.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
    void setupUi();
	void setupDockWidgets();
	void setupMenuBar();
	void createConnections();
	void closeEvent(QCloseEvent * event) Q_DECL_OVERRIDE;
	void createProject();

	private slots:
	void onNewProject();
	void onSaveProject();

private:
	//ApplicationWindow * m_applicationWindow;
	CGFF::DebugWindow * m_debugWindow;
	CGFF::AppWindow * m_appWindow;
    //QWidget *m_centralWidget;
    QMenuBar *m_menuBar;
    QToolBar *m_mainToolBar;
    QStatusBar *m_statusBar;
	QMenu * m_menuView;
	QMenu * m_menuProject;
	QAction *m_newProjectAction;
	QAction *m_saveProjectAction;

	QTUI::ExplorerView * m_explorer;
	QDockWidget * m_explorerDockWidget;

	QTUI::ObjectInfoView * m_objectInfo;
	QDockWidget * m_propertiesDockWidget;

	QMdiArea * m_mdiArea;
};

#endif
