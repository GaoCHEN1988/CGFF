#include "layer2D.h"

namespace CGFF {

    Layer2D::Layer2D(QSharedPointer<Renderer2D> renderer, QMatrix4x4 projectionMatrix, QObject *parent)
        : Layer(parent)
        , m_renderer(renderer)
    {
    }

    Layer2D::~Layer2D()
    {
    }

	void Layer2D::init()
	{
		init(m_renderer, m_material);
	}

	void Layer2D::init(QSharedPointer<Renderer2D> renderer, QSharedPointer<Material> material)
	{
	}

    void Layer2D::add(QSharedPointer<Renderable2D> renderable)
    {
        m_renderables.push_back(renderable);
    }

    QSharedPointer<Renderable2D> Layer2D::submit(QSharedPointer<Renderable2D> renderable)
    {
        m_submittedRenderables.push_back(renderable);
        return renderable;
    }

    void Layer2D::render()
    {
		m_renderer->begin();

		for (const QSharedPointer<Renderable2D> renderable : m_renderables)
			renderable->submit(m_renderer);

		for (const QSharedPointer<Renderable2D> renderable : m_submittedRenderables)
			renderable->submit(m_renderer);

		m_renderer->end();
		m_renderer->flush();
		render(m_renderer);
		m_submittedRenderables.clear();
    }

    void Layer2D::resize(int width, int height)
    {
		qSharedPointerCast<CGFF::BatchRenderer2D>(m_renderer)->setScreenSize(QSize(width, height));
    }

	void Layer2D::closeEvent(QEvent *event)
	{
		m_renderables.clear();
		m_submittedRenderables.clear();
		qSharedPointerCast<CGFF::BatchRenderer2D>(m_renderer)->close();
	}
}