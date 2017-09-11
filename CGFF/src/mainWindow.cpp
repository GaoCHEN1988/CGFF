#include "MainWindow.h"
#include "utils/qtopengl.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	//, m_applicationWindow(nullptr)
	, m_debugWindow(nullptr)
	, m_appWindow(nullptr)
	//, m_centralWidget(nullptr)
	, m_menuBar(nullptr)
	, m_mainToolBar(nullptr)
	, m_statusBar(nullptr)
	, m_menuView(nullptr)
	, m_menuProject(nullptr)
	, m_newProjectAction(nullptr)
	, m_saveProjectAction(nullptr)
	, m_explorer(nullptr)
	, m_explorerDockWidget(nullptr)
	, m_objectInfo(nullptr)
	, m_propertiesDockWidget(nullptr)
	, m_mdiArea(nullptr)
	, m_debugMdiSubWindow(nullptr)
	, m_appMdiSubWindow(nullptr)
	, m_toolBarActionStatus(true)
{
    setupUi();
}

MainWindow::~MainWindow()
{
	//delete m_applicationWindow;

	//if(m_debugWindow)
	//	delete m_debugWindow;

	m_debugWindow = nullptr;
}
void MainWindow::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(1024, 960);
    this->setMinimumSize(QSize(200, 200));
    this->setDocumentMode(false);
	this->setWindowTitle(QApplication::translate("this", "CGFF", Q_NULLPTR));

	m_mdiArea = new QMdiArea(this);
	m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(m_mdiArea);

	m_debugWindow = new CGFF::DebugWindow(this);
	m_debugWindow->setActive(true);
	QWidget * debugWidget = QWidget::createWindowContainer(m_debugWindow, this);
	m_debugMdiSubWindow = m_mdiArea->addSubWindow(debugWidget);
	m_debugMdiSubWindow->setWindowTitle("Debug");
	m_debugMdiSubWindow->setMinimumSize(400, 400);
	m_debugMdiSubWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

	m_appWindow = new CGFF::AppWindow(this);
	QWidget * appWidget = QWidget::createWindowContainer(m_appWindow, this);
	m_appMdiSubWindow = m_mdiArea->addSubWindow(appWidget);
	m_appMdiSubWindow->setWindowTitle("Application");
	m_appMdiSubWindow->setMinimumSize(400, 400);
	m_appMdiSubWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

    
    m_statusBar = new QStatusBar(this);
    m_statusBar->setObjectName(QStringLiteral("m_statusBar"));
    this->setStatusBar(m_statusBar);

	setupDockWidgets();

	setupMenuBar();

	setupToolBar();
	
	createConnections();

	onSetStatus();

    QMetaObject::connectSlotsByName(this);
} // setupUi

void MainWindow::setupDockWidgets()
{
	m_explorerDockWidget = new QDockWidget("Explorer",this);
	m_explorer = new QTUI::ExplorerView(this);
	m_explorerDockWidget->setWidget(m_explorer);

	addDockWidget(Qt::LeftDockWidgetArea, m_explorerDockWidget);

	m_propertiesDockWidget = new QDockWidget("Properties", this);
	m_objectInfo = new QTUI::ObjectInfoView(this);
	m_propertiesDockWidget->setWidget(m_objectInfo);

	addDockWidget(Qt::RightDockWidgetArea, m_propertiesDockWidget);
}

void MainWindow::setupMenuBar()
{
	m_menuBar = new QMenuBar(this);
	m_menuBar->setGeometry(QRect(0, 0, 800, 26));

	//view menu
	m_menuView = new QMenu("View", m_menuBar);
	m_menuView->addAction(m_explorerDockWidget->toggleViewAction());
	m_menuView->addAction(m_propertiesDockWidget->toggleViewAction());

	//project menu
	m_menuProject = new QMenu("Project", m_menuBar);
	m_newProjectAction = new QAction("New Project", this);
	m_newProjectAction->setShortcutContext(Qt::ApplicationShortcut);
	m_newProjectAction->setShortcut(Qt::CTRL + Qt::Key_N);
	m_menuProject->addAction(m_newProjectAction);

	m_saveProjectAction = new QAction("Save Project", this);
	m_saveProjectAction->setShortcutContext(Qt::ApplicationShortcut);
	m_saveProjectAction->setShortcut(Qt::CTRL + Qt::Key_S);
	m_menuProject->addAction(m_saveProjectAction);

	m_menuBar->addAction(m_menuProject->menuAction());
	m_menuBar->addAction(m_menuView->menuAction());

	this->setMenuBar(m_menuBar);
}

void MainWindow::setupToolBar()
{
	m_mainToolBar = new QToolBar(this);
	m_mainToolBar->setObjectName(QStringLiteral("m_mainToolBar"));

	m_playAction = new QAction("play", this);
	m_playAction->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	m_stopAction = new QAction("stop", this);
	m_stopAction->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

	m_mainToolBar->addAction(m_playAction);
	m_mainToolBar->addAction(m_stopAction);

	this->addToolBar(Qt::TopToolBarArea, m_mainToolBar);
}

void MainWindow::createConnections()
{
	connect(m_newProjectAction, &QAction::triggered,
		this, &MainWindow::onNewProject);

	connect(m_saveProjectAction, &QAction::triggered,
		this, &MainWindow::onSaveProject);

	connect(m_playAction, &QAction::triggered,
		m_appWindow, &CGFF::BaseWindow::onActivate);

	connect(m_stopAction, &QAction::triggered,
		m_appWindow, &CGFF::BaseWindow::onDisactivate);

	connect(m_playAction, &QAction::triggered,
		m_debugWindow, &CGFF::BaseWindow::onDisactivate);

	connect(m_stopAction, &QAction::triggered,
		m_debugWindow, &CGFF::BaseWindow::onActivate);

	connect(m_playAction, &QAction::triggered,
		this, &MainWindow::onSetStatus);

	connect(m_stopAction, &QAction::triggered,
		this, &MainWindow::onSetStatus);

}

void MainWindow::closeEvent(QCloseEvent * event)
{
	//foreach(QMdiSubWindow* w, m_mdiArea->subWindowList())
	//{
	//	QCoreApplication::sendEvent(w, event);
	//}
}

void MainWindow::createProject()
{

}

void MainWindow::onNewProject()
{
	if (!m_mdiArea)
		return;

	m_mdiArea->closeAllSubWindows();

}

void MainWindow::onSaveProject()
{

}

void MainWindow::onSetStatus()
{
	m_playAction->setEnabled(m_toolBarActionStatus);
	m_stopAction->setEnabled(!m_toolBarActionStatus);

	m_debugMdiSubWindow->setEnabled(m_toolBarActionStatus);
	m_appMdiSubWindow->setEnabled(!m_toolBarActionStatus);

	m_toolBarActionStatus = !m_toolBarActionStatus;
}