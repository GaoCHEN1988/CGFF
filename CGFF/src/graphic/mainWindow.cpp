#include "mainWindow.h"

mainWindow::mainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
#ifdef OPENGL_ES

#else
    QSurfaceFormat qFormat;
	qFormat.setProfile(QSurfaceFormat::CoreProfile);
	qFormat.setVersion(4, 4);
    ui.openGLWidget->setFormat(qFormat);

#endif
}

