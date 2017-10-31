#include "debugWindow.h"
#include "resource/resourceManager.h"

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

void DebugWindow::setupLayers()
{
    m_debug3DLayer = QSharedPointer<CGFF::DebugLayer3D>(new CGFF::DebugLayer3D(this->size(), m_model, m_parent));
    pushLayer(m_debug3DLayer);

    m_debugLayer = QSharedPointer<CGFF::DebugLayer>(new CGFF::DebugLayer(this->size(), m_parent));
    pushOverlay(m_debugLayer);
}
