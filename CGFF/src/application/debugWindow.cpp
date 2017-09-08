#include "debugWindow.h"
#include "debug/debugLayer.h"
#include "Debug/debugLayer3D.h"

namespace CGFF {

	DebugWindow * DebugWindow::m_instance = nullptr;
	
	DebugWindow::DebugWindow(QWidget * parent, CGFF::RenderAPI api)
		: BaseWindow(parent, api)
	{
		m_instance = this;
	}
	DebugWindow::~DebugWindow()
	{
	}

	void DebugWindow::initialize()
	{
		BaseWindow::initialize();
		pushLayer(QSharedPointer<CGFF::DebugLayer3D>(new CGFF::DebugLayer3D(this->size(), m_parent)));
		pushOverlay(QSharedPointer<CGFF::DebugLayer>(new CGFF::DebugLayer(this->size(), m_parent)));
	}


}