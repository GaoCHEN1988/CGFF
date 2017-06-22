#include "mainWindow.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>

/*
//Test
#include <QVector>
#include <QSharedPointer>
#include <iostream>
class A
{
public:
    A()
    {
        std::cout << "Construct A" << std::endl;
    };

    ~A()
    {
        std::cout << "destruct A" << std::endl;
    };
};
void test()
{
    QSharedPointer<A> a1 = QSharedPointer<A>(new A);
    QSharedPointer<A> a2 = QSharedPointer<A>(new A);
    QSharedPointer<A> a3 = QSharedPointer<A>(new A);
    QSharedPointer<A> a4 = QSharedPointer<A>(new A);
    QVector<QSharedPointer<A>> vector;
    vector.push_back(QSharedPointer<A>(new A));
    vector.push_back(QSharedPointer<A>(new A));
    vector.push_back(QSharedPointer<A>(new A));
    vector.clear();
    vector.push_back(a4);
}


int main(int argc, char *argv[])
{
    test();
    return 0;
}
*/


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mainWindow w;
	w.show();
	return a.exec();
}
