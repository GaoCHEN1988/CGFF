#include "debugLayer.h"
#include "graphic/shaderFactory/shaderFasctory.h"

namespace CGFF {

    DebugLayer::DebugLayer(QSize screenSize)
        : Layer2D(QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D(screenSize)), DefaultShader())
    {
        m_isVisible = false;
    }

    void DebugLayer::init()
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::SCREEN);

        DebugMenu::init();
        DebugMenu::setVisible(true);
        DebugMenu::add("Example Item");
        DebugMenu::add("This is another example");
    }

    void DebugLayer::render()
    {
        Layer2D::render();

        if (DebugMenu::isVisible())
        {
            DebugMenu::render(m_renderer);
        }
    }

    void DebugLayer::resize(int width, int height)
    {
        CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        m_projectionMatrix.setToIdentity();
        m_projectionMatrix.ortho(0, GLfloat(width), 0, GLfloat(height), 0.0f, 100.0f);
    }

    void DebugLayer::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Control)
        {
            m_isVisible = !m_isVisible;
        }
    }
}