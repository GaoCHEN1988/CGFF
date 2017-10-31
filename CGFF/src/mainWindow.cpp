#include "MainWindow.h"
#include "utils/qtopengl.h"
#include "system/fileSystem/vfs.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QListView>
#include <QGridLayout>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_learnGLWindow(nullptr)
	, m_debugWindow(nullptr)
	, m_menuBar(nullptr)
	, m_mainToolBar(nullptr)
	, m_statusBar(nullptr)
	, m_menuView(nullptr)
	, m_menuGeometry(nullptr)
	, m_menuLight(nullptr)
	, m_menuCamera(nullptr)
    , m_menuLoad(nullptr)
	, m_menuProject(nullptr)
	, m_newProjectAction(nullptr)
	, m_saveProjectAction(nullptr)
	, m_playAction(nullptr)
	, m_stopAction(nullptr)
	, m_cubeAction(nullptr)
	, m_sphereAction(nullptr)
	, m_planeAction(nullptr)
	, m_directionalLightAction(nullptr)
	, m_mayaCameraAction(nullptr)
    , m_loadModelAction(nullptr)
    , m_loadSkyBoxImagesAction(nullptr)
	, m_explorer(nullptr)
	, m_explorerDockWidget(nullptr)
	, m_objectInfo(nullptr)
	, m_propertiesDockWidget(nullptr)
	, m_toolBarActionStatus(true)
	, m_objectList(nullptr)
	, m_objectListDockWidget(nullptr)
	, m_resourceModel(nullptr)
    , m_renderApi(CGFF::RenderAPI::OPENGL)
{
    setupUi();
    init();

}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
    CGFF::Context::setRenderAPI(m_renderApi);
}

void MainWindow::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(1024, 960);
    this->setMinimumSize(QSize(200, 200));
    this->setDocumentMode(false);
	this->setWindowTitle(QApplication::translate("this", "CGFF", Q_NULLPTR));

    m_resourceModel = new QTUI::ResourceModel(this);

	m_debugWindow = new DebugWindow(this, m_renderApi);
	m_debugWindow->setActive(true);
    m_debugWindow->setModel(m_resourceModel);

    //m_learnGLWindow = new CGFF::LearnGLWindow(this);
    //m_learnGLWindow->setActive(true);
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
    //Explorer Widget should always be set up at first
	m_explorerDockWidget = new QDockWidget("Explorer",this);
	m_explorer = new QTUI::ExplorerView(this);
	m_explorerDockWidget->setWidget(m_explorer);

	addDockWidget(Qt::LeftDockWidgetArea, m_explorerDockWidget);

	m_objectListDockWidget = new QDockWidget("Hierarchy", this);
	m_objectList = new QTUI::ObjectListView(this);
	m_objectList->setModel(m_resourceModel);
	m_objectListDockWidget->setWidget(m_objectList);

	addDockWidget(Qt::RightDockWidgetArea, m_objectListDockWidget);

	m_propertiesDockWidget = new QDockWidget("Properties", this);
	m_objectInfo = new QTUI::ObjectInfoView(this);
	m_objectInfo->setModel(m_resourceModel);
  
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
    m_menuView->addAction(m_objectListDockWidget->toggleViewAction());

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
	m_directionalLightAction = new QAction("Directional Light", this);
	m_menuLight->addAction(m_directionalLightAction);

	//camera menu
	m_menuCamera = new QMenu("Camera", m_menuBar);
	m_mayaCameraAction = new QAction("Maya Camera", this);
	m_menuCamera->addAction(m_mayaCameraAction);

    //Load Menu
    m_menuLoad = new QMenu("Load", m_menuBar);
    m_loadModelAction = new QAction("Model", this);
    m_menuLoad->addAction(m_loadModelAction);

    m_loadSkyBoxImagesAction = new QAction("Sky box from images", this);
    m_menuLoad->addAction(m_loadSkyBoxImagesAction);

    m_menuBar->addAction(m_menuProject->menuAction());
    m_menuBar->addAction(m_menuLoad->menuAction());
	m_menuBar->addAction(m_menuGeometry->menuAction());
	m_menuBar->addAction(m_menuLight->menuAction());
	m_menuBar->addAction(m_menuCamera->menuAction());
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
	connect(m_newProjectAction, &QAction::triggered, this, &MainWindow::onNewProject);
	connect(m_saveProjectAction, &QAction::triggered, this, &MainWindow::onSaveProject);
	connect(m_cubeAction, &QAction::triggered, [=]() { m_resourceModel->onAddEntity(CGFF::EntityType::CUBE); });
	connect(m_sphereAction, &QAction::triggered, [=]() { m_resourceModel->onAddEntity(CGFF::EntityType::SPHERE); });
    connect(m_planeAction, &QAction::triggered, [=]() { m_resourceModel->onAddEntity(CGFF::EntityType::PLANE); });
    connect(m_loadModelAction, &QAction::triggered, this, &MainWindow::onLoadModel);
    connect(m_loadSkyBoxImagesAction, &QAction::triggered, this, &MainWindow::onLoadSkyBoxImages);
    connect(m_directionalLightAction, &QAction::triggered, [=]() { m_resourceModel->onAddLight(CGFF::LightType::DIRECTIONAL); });
	connect(m_playAction, &QAction::triggered, this, &MainWindow::onSetStatus);
	connect(m_stopAction, &QAction::triggered, this, &MainWindow::onSetStatus);
    connect(m_debugWindow, &DebugWindow::initilizeSignal, m_explorer, &QTUI::ExplorerView::onInitilize);
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

//Load model object from .obj file
void MainWindow::onLoadModel()
{
    QFileDialog dialog;
    QString directoryName = CGFF::VFS::get()->getMountedPhysicalPath("resource");
    dialog.setDirectory(directoryName);
    QString fileName = dialog.getOpenFileName(this,
        tr("Load model"), "",
        tr("Model (*.obj)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        m_resourceModel->onLoadModel(fileName);
    }

}

void MainWindow::onLoadSkyBoxImages()
{
    QFileDialog dialog;
    QString directoryName = CGFF::VFS::get()->getMountedPhysicalPath("resource");
    dialog.setDirectory(directoryName);
    QStringList fileNames = dialog.getOpenFileNames(this,
        tr("Chose 6 Texture Images"), "",
        tr("Image (*.png; *.jpg; *.tng; *.bmp)"));

    if (!fileNames.isEmpty())
    {
        if (fileNames.size() != 6)
        {
            QMessageBox::information(this, tr("Unable to import images"), tr("Must have 6 images for cube texture!"));
            return;
        }

        QDialog  listDialog(nullptr, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(buttonBox, SIGNAL(accepted()), &listDialog, SLOT(accept()));
        connect(buttonBox, SIGNAL(rejected()), &listDialog, SLOT(reject()));

        QGridLayout* layout = new QGridLayout(&listDialog);

        QComboBox* left = new QComboBox(&listDialog);
        QLabel * left_label = new QLabel("Left[+x]", &listDialog);
        left->addItems(fileNames);

        QComboBox* right = new QComboBox(&listDialog);
        QLabel * right_label = new QLabel("Right[-x]", &listDialog);
        right->addItems(fileNames);

        QComboBox* up = new QComboBox(&listDialog);
        QLabel * up_label = new QLabel("Up[+y]", &listDialog);
        up->addItems(fileNames);

        QComboBox* down = new QComboBox(&listDialog);
        QLabel * down_label = new QLabel("Down[-y]", &listDialog);
        down->addItems(fileNames);

        QComboBox* front = new QComboBox(&listDialog);
        QLabel * front_label = new QLabel("Front[+z]", &listDialog);
        front->addItems(fileNames);

        QComboBox* back = new QComboBox(&listDialog);
        QLabel * back_label = new QLabel("Back[-Z]", &listDialog);
        back->addItems(fileNames);

        layout->addWidget(left_label, 0, 0, 1, 1);
        layout->addWidget(left, 0, 1, 1, 3);

        layout->addWidget(right_label, 1, 0);
        layout->addWidget(right, 1, 1, 1, 3);

        layout->addWidget(up_label, 2, 0);
        layout->addWidget(up, 2, 1, 1, 3);

        layout->addWidget(down_label, 3, 0);
        layout->addWidget(down, 3, 1, 1, 3);

        layout->addWidget(front_label, 4, 0);
        layout->addWidget(front, 4, 1, 1, 3);

        layout->addWidget(back_label, 5, 0);
        layout->addWidget(back, 5, 1, 1, 3);

        layout->addWidget(buttonBox, 6, 3);

        if (listDialog.exec() == QDialog::Accepted)
        {
            QStringList sortedFileNames;

            sortedFileNames.append(left->currentText());
            sortedFileNames.append(right->currentText());
            sortedFileNames.append(up->currentText());
            sortedFileNames.append(down->currentText());
            sortedFileNames.append(front->currentText());
            sortedFileNames.append(back->currentText());

            if (sortedFileNames.size() == 6)
                m_resourceModel->onLoadSkyBox(sortedFileNames);
        }

    }
}