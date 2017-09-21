#include "debugWindow.h"
#include "resource/resourceManager.h"

namespace CGFF {

	DebugWindow * DebugWindow::m_instance = nullptr;
	
	DebugWindow::DebugWindow(QWidget * parent, CGFF::RenderAPI api)
		: BaseWindow(parent, api)
		, m_debug3DLayer(nullptr)
		, m_debugLayer(nullptr)
	{
		m_instance = this;
	}

	DebugWindow::~DebugWindow()
	{
	}

	void DebugWindow::onAddEntity(const QString& name)
	{
		m_debug3DLayer->addEntity(name);
	}

	void DebugWindow::setupLayers()
	{
		//if (!m_debug3DLayer)
		{
			m_debug3DLayer = QSharedPointer<CGFF::DebugLayer3D>(new CGFF::DebugLayer3D(this->size(), m_parent));
			pushLayer(m_debug3DLayer);
		}

		//if (!m_debugLayer)
		{
			m_debugLayer = QSharedPointer<CGFF::DebugLayer>(new CGFF::DebugLayer(this->size(), m_parent));
			pushOverlay(m_debugLayer);
		}
	}
}