#include "layer2D.h"
#include "graphic/renderer/renderer.h"

namespace CGFF {

    Layer2D::Layer2D(QSize size, QWidget *parent ,QMatrix4x4 projectionMatrix)
        : Layer(parent)
		, m_size(size)
    {
		m_renderer = QSharedPointer<BatchRenderer2D>(new BatchRenderer2D(QSize(m_size.width(), m_size.height())));
		m_scene2D = QSharedPointer<Scene2D>(new Scene2D(m_size, projectionMatrix));
		m_renderer->setCamera(m_scene2D->getCamera());
    }

	Layer2D::Layer2D(QSharedPointer<Scene2D> scene, QWidget *parent)
		: Layer(parent)
		, m_scene2D(scene)
	{
		m_renderer = QSharedPointer<BatchRenderer2D>(new BatchRenderer2D(QSize(m_size.width(), m_size.height())));
		m_renderer->setCamera(m_scene2D->getCamera());
	}

    Layer2D::~Layer2D()
    {
    }

    //void Layer2D::add(QSharedPointer<Renderable2D> renderable)
    //{
    //    m_renderables.push_back(renderable);
    //}

	void Layer2D::add(QSharedPointer<Sprite> sprite)
	{
		QMatrix4x4 trans;
		trans.translate(sprite->getPosition());
		m_scene2D->add(QSharedPointer<Entity>(new Entity(sprite, trans)));
	}

    QSharedPointer<Renderable2D> Layer2D::submit(QSharedPointer<Renderable2D> renderable)
    {
        m_submittedRenderables.push_back(renderable);
        return renderable;
    }

    void Layer2D::render()
    {
		m_scene2D->render();
		m_renderer->begin();

		for (const QSharedPointer<Renderable2D> renderable : m_submittedRenderables)
			renderable->submit(m_renderer);

		render(m_renderer);
		m_renderer->end();
		m_renderer->flush();
		m_submittedRenderables.clear();
    }

	void Layer2D::resizeEvent(QResizeEvent *event)
	{
		m_size = event->size();
        GLCall(Renderer::setViewport(0, 0, m_size.width(), m_size.height()));
        qSharedPointerCast<CGFF::BatchRenderer2D>(m_renderer)->setScreenSize(event->size());
        qSharedPointerCast<CGFF::BatchRenderer2D>(m_renderer)->setViewportSize(event->size());
		m_scene2D->getRenderer()->setScreenSize(event->size());
        m_scene2D->getRenderer()->setViewportSize(event->size());
	}

	void Layer2D::closeEvent(QCloseEvent *event)
	{
		m_submittedRenderables.clear();
		m_renderer->close();
		m_scene2D->close();
	}
}