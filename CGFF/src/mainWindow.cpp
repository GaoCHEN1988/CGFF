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
	QWidget * debugWidget = QWidget::createWindowContainer(m_debugWindow, this);
	QMdiSubWindow * debugMdiSubWindow = m_mdiArea->addSubWindow(debugWidget);
	debugMdiSubWindow->setWindowTitle("Debug");
	debugMdiSubWindow->setMinimumSize(400, 400);

	//m_appWindow = new CGFF::AppWindow(m_mdiArea);
	//QWidget * appWidget = QWidget::createWindowContainer(m_appWindow, this);
	//QMdiSubWindow * appMdiSubWindow = m_mdiArea->addSubWindow(appWidget);
	//appMdiSubWindow->setWindowTitle("Application");
	//appMdiSubWindow->setMinimumSize(400, 400);
    
    m_mainToolBar = new QToolBar(this);
    m_mainToolBar->setObjectName(QStringLiteral("m_mainToolBar"));
    m_mainToolBar->setMinimumSize(QSize(0, 0));
    this->addToolBar(Qt::TopToolBarArea, m_mainToolBar);
    m_statusBar = new QStatusBar(this);
    m_statusBar->setObjectName(QStringLiteral("m_statusBar"));
    this->setStatusBar(m_statusBar);

	setupDockWidgets();

	setupMenuBar();

	createConnections();

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

void MainWindow::createConnections()
{
	connect(m_newProjectAction, &QAction::triggered,
		this, &MainWindow::onNewProject);

	connect(m_saveProjectAction, &QAction::triggered,
		this, &MainWindow::onSaveProject);
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