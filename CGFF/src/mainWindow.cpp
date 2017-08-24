#include "MainWindow.h"
#include "utils/qtopengl.h"
#include "application/applicationWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    setupUi();
}

void MainWindow::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));
    this->resize(800, 600);
    this->setMinimumSize(QSize(200, 200));
    this->setDocumentMode(false);

    //centralWidget = new QWidget(this);
	centralWidget = QWidget::createWindowContainer(new ApplicationWindow, this);

    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    //openGLWidget = new ApplicationWidget(centralWidget);
    //openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

    //gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

    this->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 800, 26));
    this->setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    mainToolBar->setMinimumSize(QSize(0, 0));
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    this->setStatusBar(statusBar);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
} // setupUi

void MainWindow::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("this", "CGFF", Q_NULLPTR));
} // retranslateUi