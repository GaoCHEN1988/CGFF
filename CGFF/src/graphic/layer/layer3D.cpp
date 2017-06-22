#include "layer3D.h"

namespace CGFF {

    Layer3D::Layer3D(QSharedPointer<Scene> scene)
        : m_scene(scene)
        , m_renderer(QSharedPointer<Renderer3D>(new ForwardRenderer()))
    {
    }
    Layer3D::~Layer3D()
    {
    }

    void Layer3D::init()
    {
    }

    void Layer3D::render()
    {
        m_scene->render(m_renderer);
        m_renderer->flush();
    }

}