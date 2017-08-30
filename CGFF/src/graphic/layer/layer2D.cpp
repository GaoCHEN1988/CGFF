#include "layer2D.h"

namespace CGFF {

    Layer2D::Layer2D(QMatrix4x4 projectionMatrix, QObject *parent)
        : Layer(parent)
    {
		m_renderer = QSharedPointer<BatchRenderer2D>(new BatchRenderer2D(QSize(g_openglWidgetSize.width(), g_openglWidgetSize.height())));
		m_scene2D = QSharedPointer<Scene2D>(new Scene2D(projectionMatrix));
		m_renderer->setCamera(m_scene2D->getCamera());
    }

	Layer2D::Layer2D(QSharedPointer<Scene2D> scene, QObject *parent)
		: Layer(parent)
		, m_scene2D(scene)
	{
		m_renderer = QSharedPointer<BatchRenderer2D>(new BatchRenderer2D(QSize(g_openglWidgetSize.width(), g_openglWidgetSize.height())));
		m_renderer->setCamera(m_scene2D->getCamera());
	}

    Layer2D::~Layer2D()
    {
    }

	void Layer2D::init()
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

    void Layer2D::resize(int width, int height)
    {
		qSharedPointerCast<CGFF::BatchRenderer2D>(m_renderer)->setScreenSize(QSize(width, height));
		m_scene2D->getRenderer()->setScreenSize(QSize(width, height));
    }

	void Layer2D::closeEvent(QEvent *event)
	{
		m_submittedRenderables.clear();
		m_renderer->close();
		m_scene2D->close();
	}
}