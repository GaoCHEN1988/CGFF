#include "debugLayer.h"
#include "graphic/shaderFactory/shaderFasctory.h"

namespace CGFF {

    DebugLayer::DebugLayer(QSize screenSize)
        : Layer2D(QSharedPointer<CGFF::BatchRenderer2D>(new CGFF::BatchRenderer2D(screenSize)), DefaultShader())
    {
    }

    void DebugLayer::init()
    {
        Layer2D::getRenderer()->setRenderTarget(CGFF::RenderTarget::SCREEN);
        for (int i = 0; i < 5; i++)
        {
            float y = 40*i + 200;
            Layer2D::add(QSharedPointer<CGFF::Sprite>(new CGFF::Sprite(0, y, 100, 33, QVector4D(0.564f, 0.564f, 0.564f, 0.564f))));
            Layer2D::add(QSharedPointer<CGFF::Label>(new CGFF::Label("Item " + QString::number(i + 1), 0, i*40 + 200, QVector4D(1, 1, 1, 1))));
        }
    }

    void DebugLayer::render()
    {
        Layer2D::render();
    }

    void DebugLayer::resize(int width, int height)
    {
        CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        m_projectionMatrix.setToIdentity();
        m_projectionMatrix.ortho(0, GLfloat(width), 0, GLfloat(height), 0.0f, 100.0f);
    }
}