#ifndef CGFF_MAINWINDOW_H
#define CGFF_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDockWidget>
#include "application/applicationWindow.h"
#include "qtUI/explorerView.h"
#include "qtUI/view/objectInfoView.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
    void setupUi();
    void retranslateUi();
	void setupDockWidgets();
	void setupMenuBar();
	void closeEvent(QCloseEvent * event) Q_DECL_OVERRIDE;

private:
	ApplicationWindow * m_applicationWindow;
    QWidget *m_centralWidget;
    QGridLayout *gridLayout;
    QMenuBar *m_menuBar;
    QToolBar *m_mainToolBar;
    QStatusBar *m_statusBar;
	QMenu * m_menuView;
	QAction *m_actionExplorerView;

	QTUI::ExplorerView * m_explorer;
	QDockWidget * m_explorerDockWidget_;

	QTUI::ObjectInfoView * m_objectInfo;
	QDockWidget * m_propertiesDockWidget_;
};

#endif
