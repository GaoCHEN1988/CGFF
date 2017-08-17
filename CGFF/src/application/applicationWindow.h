#pragma once
#include <QWindow>

class ApplicationWindow : public QWindow {
	Q_OBJECT

public:
	ApplicationWindow(QWindow * parent = Q_NULLPTR);
	~ApplicationWindow();

private:
	
};
