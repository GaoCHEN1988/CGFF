#include "learnGLWindow.h"

namespace CGFF {
   
    LearnGLWindow * LearnGLWindow::m_instance = nullptr;

    LearnGLWindow::LearnGLWindow(QWidget * parent, CGFF::RenderAPI api)
        : BaseWindow(parent, api)
        , m_appDLayer(nullptr)
    {
        m_instance = this;
    }

    LearnGLWindow::~LearnGLWindow()
    {
    }

    void LearnGLWindow::setupLayers()
    {
        m_appDLayer = QSharedPointer<CGFF::App3DLayer>(new CGFF::App3DLayer(this->size(), m_parent));
        pushLayer(m_appDLayer);

        ////Only for test
        //m_test2DLayer = QSharedPointer<CGFF::Test2DLayer>(new CGFF::Test2DLayer(this->size(), m_parent));       
        //pushOverlay(m_test2DLayer);
    }
}