#include "MainWindow.h"
#include "utils/qtopengl.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	//, m_applicationWindow(nullptr)
	, m_debugWindow(nullptr)
	//, m_centralWidget(nullptr)
	, m_menuBar(nullptr)
	, m_mainToolBar(nullptr)
	, m_statusBar(nullptr)
	, m_menuView(nullptr)
	, m_menuGeometry(nullptr)
	, m_menuLight(nullptr)
	, m_menuCamera(nullptr)
	, m_menuProject(nullptr)
	, m_newProjectAction(nullptr)
	, m_saveProjectAction(nullptr)
	, m_playAction(nullptr)
	, m_stopAction(nullptr)
	, m_cubeAction(nullptr)
	, m_sphereAction(nullptr)
	, m_planeAction(nullptr)
	, m_lightAction(nullptr)
	, m_mayaCameraAction(nullptr)
	, m_explorer(nullptr)
	, m_explorerDockWidget(nullptr)
	, m_objectInfo(nullptr)
	, m_propertiesDockWidget(nullptr)
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

	m_debugWindow = new CGFF::DebugWindow(this);
	m_debugWindow->setActive(true);
	QWidget * debugWidget = QWidget::createWindowContainer(m_debugWindow, this);
	setCentralWidget(debugWidget);
	
    
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

	//geometry menu
	m_menuGeometry = new QMenu("Geometry", m_menuBar);
	m_cubeAction = new QAction("Cube", this);
	m_sphereAction = new QAction("Sphere", this);
	m_planeAction = new QAction("Plane", this);
	m_menuGeometry->addAction(m_cubeAction);
	m_menuGeometry->addAction(m_sphereAction);
	m_menuGeometry->addAction(m_planeAction);

	//light menu
	m_menuLight = new QMenu("Light", m_menuBar);
	m_lightAction = new QAction("Light", this);
	m_menuLight->addAction(m_lightAction);

	//camera menu
	m_menuCamera = new QMenu("Camera", m_menuBar);
	m_mayaCameraAction = new QAction("Maya Camera", this);
	m_menuCamera->addAction(m_mayaCameraAction);

	m_menuBar->addAction(m_menuProject->menuAction());
	m_menuBar->addAction(m_menuView->menuAction());
	m_menuBar->addAction(m_menuGeometry->menuAction());
	m_menuBar->addAction(m_menuLight->menuAction());
	m_menuBar->addAction(m_menuCamera->menuAction());

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
		m_debugWindow, &CGFF::BaseWindow::onDisactivate);

	connect(m_stopAction, &QAction::triggered,
		m_debugWindow, &CGFF::BaseWindow::onActivate);

	connect(m_cubeAction, &QAction::triggered, [=]() { m_debugWindow->onAddEntity(CGFF::EntityType::CUBE); });
	connect(m_sphereAction, &QAction::triggered, [=]() { m_debugWindow->onAddEntity(CGFF::EntityType::SPHERE); });
	connect(m_planeAction, &QAction::triggered, [=]() { m_debugWindow->onAddEntity(CGFF::EntityType::PLANE); });

	connect(m_playAction, &QAction::triggered,
		this, &MainWindow::onSetStatus);

	connect(m_stopAction, &QAction::triggered,
		this, &MainWindow::onSetStatus);

}

void MainWindow::createProject()
{

}

void MainWindow::onNewProject()
{

}

void MainWindow::onSaveProject()
{

}

void MainWindow::onSetStatus()
{
	m_playAction->setEnabled(m_toolBarActionStatus);
	m_stopAction->setEnabled(!m_toolBarActionStatus);
	m_toolBarActionStatus = !m_toolBarActionStatus;
}