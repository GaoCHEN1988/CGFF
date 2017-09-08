#include "appWindow.h"
#include "examples/test3DLayer.h"
#include "examples/test2DLayer.h"

namespace CGFF {

	AppWindow::AppWindow(QWidget * parent, CGFF::RenderAPI api)
		: BaseWindow(parent, api)
	{
	}

	AppWindow::~AppWindow()
	{
	}

	void AppWindow::initialize()
	{
		BaseWindow::initialize();
		pushLayer(QSharedPointer<CGFF::Layer>(new CGFF::Test3DLayer(this->size(), m_parent)));
		pushOverlay(QSharedPointer<CGFF::Layer>(new CGFF::Test2DLayer(this->size(), m_parent)));
	}

}