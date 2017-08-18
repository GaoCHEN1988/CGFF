#include "mainWindow.h"
#include <QtWidgets/QApplication>
#include <QApplication>

#include "application/applicationWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//MainWindow w;
	//w.show();

	ApplicationWindow app;
	app.show();

	return a.exec();
}
