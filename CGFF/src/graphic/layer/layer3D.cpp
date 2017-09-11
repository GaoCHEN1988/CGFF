#include "layer3D.h"

namespace CGFF {

    Layer3D::Layer3D(QSharedPointer<Scene> scene, QSharedPointer<Renderer3D> renderer, QWidget *parent)
        : Layer(parent)
		, m_scene(scene)
        , m_renderer(renderer)
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
		render(m_renderer);
        m_renderer->flush();
    }

	void Layer3D::resizeEvent(QResizeEvent *event)
	{
		m_renderer->setScreenBufferSize(event->size().width(), event->size().height());
	}

	void Layer3D::closeEvent(QCloseEvent *event)
	{
		m_renderer->close();
		m_scene->close();
	}
}