#include "MainWindow.h"
#include "utils/qtopengl.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_applicationWindow(nullptr)
	, m_centralWidget(nullptr)
	, gridLayout(nullptr)
	, m_menuBar(nullptr)
	, m_mainToolBar(nullptr)
	, m_statusBar(nullptr)
	, m_menuView(nullptr)
	, m_actionExplorerView(nullptr)
	, m_explorer(nullptr)
	, m_explorerDockWidget_(nullptr)
	, m_objectInfo(nullptr)
	, m_propertiesDockWidget_(nullptr)
{
    setupUi();
}

MainWindow::~MainWindow()
{
	delete m_applicationWindow;
}
void MainWindow::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(1024, 960);
    this->setMinimumSize(QSize(200, 200));
    this->setDocumentMode(false);

	m_applicationWindow = new ApplicationWindow;
	m_centralWidget = QWidget::createWindowContainer(m_applicationWindow, this);

    m_centralWidget->setObjectName(QStringLiteral("m_centralWidget"));
    gridLayout = new QGridLayout(m_centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    this->setCentralWidget(m_centralWidget);
    
    m_mainToolBar = new QToolBar(this);
    m_mainToolBar->setObjectName(QStringLiteral("m_mainToolBar"));
    m_mainToolBar->setMinimumSize(QSize(0, 0));
    this->addToolBar(Qt::TopToolBarArea, m_mainToolBar);
    m_statusBar = new QStatusBar(this);
    m_statusBar->setObjectName(QStringLiteral("m_statusBar"));
    this->setStatusBar(m_statusBar);

	setupDockWidgets();

	setupMenuBar();

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
} // setupUi

void MainWindow::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("this", "CGFF", Q_NULLPTR));
} // retranslateUi

void MainWindow::setupDockWidgets()
{
	m_explorerDockWidget_ = new QDockWidget("Explorer",this);
	m_explorer = new QTUI::ExplorerView(this);
	m_explorerDockWidget_->setWidget(m_explorer);

	addDockWidget(Qt::LeftDockWidgetArea, m_explorerDockWidget_);

	m_propertiesDockWidget_ = new QDockWidget("Properties", this);
	m_objectInfo = new QTUI::ObjectInfoView(this);
	m_propertiesDockWidget_->setWidget(m_objectInfo);

	addDockWidget(Qt::RightDockWidgetArea, m_propertiesDockWidget_);
}

void MainWindow::setupMenuBar()
{
	m_menuBar = new QMenuBar(this);
	m_menuBar->setGeometry(QRect(0, 0, 800, 26));

	m_menuView = new QMenu("View", m_menuBar);
	m_menuView->addAction(m_explorerDockWidget_->toggleViewAction());
	m_menuView->addAction(m_propertiesDockWidget_->toggleViewAction());

	m_menuBar->addAction(m_menuView->menuAction());

	this->setMenuBar(m_menuBar);
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	QCoreApplication::sendEvent(m_applicationWindow, event);
}
