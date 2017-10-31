#include "learnGLWindow.h"


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
        m_appDLayer = QSharedPointer<CGFF::App3DLayer>(new CGFF::App3DLayer(this->size(), m_model, m_parent));
        pushLayer(m_appDLayer);
    }