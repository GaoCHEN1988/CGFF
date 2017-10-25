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
#include "application/learnGLWindow.h"
#include "qtUI/view/explorerView.h"
#include "qtUI/view/objectInfoView.h"
#include "qtUI/view/objectListView.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
    void init();
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
    void onLoadModel();
    void onLoadSkyBoxImages();

private:
    CGFF::RenderAPI m_renderApi;
	//ApplicationWindow * m_applicationWindow;
	CGFF::DebugWindow * m_debugWindow;
    CGFF::LearnGLWindow * m_learnGLWindow;

    QMenuBar *m_menuBar;
    QToolBar *m_mainToolBar;
    QStatusBar *m_statusBar;
	QMenu * m_menuView;
	QMenu * m_menuProject;
	QMenu * m_menuGeometry;
	QMenu * m_menuLight;
    QMenu * m_menuCamera;
    QMenu * m_menuLoad;
	QAction *m_newProjectAction;
	QAction *m_saveProjectAction;
	QAction *m_playAction;
	QAction *m_stopAction;
	//Geometry actions
	QAction *m_cubeAction;
	QAction *m_sphereAction;
	QAction *m_planeAction;
    //Light actions
	QAction *m_directionalLightAction;
    //camera actions
	QAction *m_mayaCameraAction;
    //Load actions
    QAction *m_loadModelAction;
    QAction *m_loadSkyBoxImagesAction;

	QTUI::ExplorerView * m_explorer;
	QDockWidget * m_explorerDockWidget;

	QTUI::ObjectInfoView * m_objectInfo;
	QDockWidget * m_propertiesDockWidget;
	bool m_toolBarActionStatus;

	QTUI::ObjectListView* m_objectList;
	QDockWidget * m_objectListDockWidget;

	QTUI::ResourceModel * m_resourceModel;
};

#endif
