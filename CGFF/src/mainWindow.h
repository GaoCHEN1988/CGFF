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
#include <QPushButton>

//#include "application/applicationWindow.h"
#include "application/debugWindow.h"
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
	void setupToolBar();
	void createConnections();
	void createProject();

	private slots:
	void onNewProject();
	void onSaveProject();
	void onSetStatus();

private:
	//ApplicationWindow * m_applicationWindow;
	CGFF::DebugWindow * m_debugWindow;
    //QWidget *m_centralWidget;
    QMenuBar *m_menuBar;
    QToolBar *m_mainToolBar;
    QStatusBar *m_statusBar;
	QMenu * m_menuView;
	QMenu * m_menuProject;
	QMenu * m_menuGeometry;
	QMenu * m_menuLight;
	QMenu * m_menuCamera;
	QAction *m_newProjectAction;
	QAction *m_saveProjectAction;
	QAction *m_playAction;
	QAction *m_stopAction;
	//Geometry actions
	QAction *m_cubeAction;
	QAction *m_sphereAction;
	QAction *m_planeAction;
	QAction *m_lightAction;
	QAction *m_mayaCameraAction;

	QTUI::ExplorerView * m_explorer;
	QDockWidget * m_explorerDockWidget;

	QTUI::ObjectInfoView * m_objectInfo;
	QDockWidget * m_propertiesDockWidget;
	bool m_toolBarActionStatus;
};

#endif
