#include "appWindow.h"
#include "examples/test3DLayer.h"
#include "examples/test2DLayer.h"
#include "examples/app3DLayer.h"

namespace CGFF {

	AppWindow::AppWindow(QWidget * parent, CGFF::RenderAPI api)
		: BaseWindow(parent, api)
	{
	}

	AppWindow::~AppWindow()
	{
	}

	void AppWindow::setupLayers()
	{
		pushLayer(QSharedPointer<CGFF::Layer>(new CGFF::Test3DLayer(this->size(), m_parent)));
		pushOverlay(QSharedPointer<CGFF::Layer>(new CGFF::Test2DLayer(this->size(), m_parent)));
        //pushLayer(QSharedPointer<CGFF::Layer>(new CGFF::App3DLayer(this->size(), m_parent)));
	}

}