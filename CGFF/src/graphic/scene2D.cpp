#include "scene2D.h"

namespace CGFF {
	Scene2D::Scene2D(const QSize& size)
		: m_size(size)
	{
		QMatrix4x4 proj = QMatrix4x4();
		proj.ortho(0, (float)m_size.width(), 0, (float)m_size.height(), -1.0f, 100.0f);

		m_camera = QSharedPointer<OrthographicCamera>(new OrthographicCamera(proj));
		m_renderer = QSharedPointer<BatchRenderer2D>(new BatchRenderer2D(QSize(m_size.width(), m_size.height())));
		m_renderer->setCamera(m_camera);
	}

	Scene2D::Scene2D(const QSize& size, const QMatrix4x4& projectionMatrix)
		: m_size(size)
		, m_camera(QSharedPointer<OrthographicCamera>(new OrthographicCamera(projectionMatrix)))
	{
		m_renderer = QSharedPointer<BatchRenderer2D>(new BatchRenderer2D(QSize(m_size.width(), m_size.height())));
		m_renderer->setCamera(m_camera);
	}

	Scene2D::~Scene2D()
	{}

	void Scene2D::add(QSharedPointer<Entity> entity)
	{
		m_entities.push_back(entity);
	}

	void Scene2D::render()
	{
		m_camera->update();
		m_renderer->begin();
		for (uint i = 0; i < m_entities.size(); i++)
		{
			QSharedPointer<Entity> entity = m_entities[i];
			SpriteComponent* sprite = entity->getComponent<SpriteComponent>();
			if (sprite)
			{
				TransformComponent* tc = entity->getComponent<TransformComponent>();
				Q_ASSERT(tc); // Sprites MUST have transforms
				sprite->sprite->submit(m_renderer);
			}

		}

		m_renderer->end();
		m_renderer->flush();
	}

	void Scene2D::close()
	{
		m_entities.clear();
		m_renderer->close();
	}
}