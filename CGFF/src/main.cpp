#include "mainWindow.h"
#include <QtWidgets/QApplication>
#include <QApplication>

#include "application/applicationWindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	//ApplicationWindow app;
	//app.show();

	return a.exec();
}
