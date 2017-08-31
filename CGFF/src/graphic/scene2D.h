#ifndef CGFF_SCENE_2D_H
#define CGFF_SCENE_2D_H

#include "renderer/batchRenderer2d.h"
#include "entity/entity.h"
#include "camera/orthographicCamera.h"

namespace CGFF {

	class Scene2D
	{
	public:
		Scene2D();
		Scene2D(const QMatrix4x4& projectionMatrix);
		virtual ~Scene2D();

		void add(QSharedPointer<Entity> entity);
		void render();
		void close();

		inline QSharedPointer<BatchRenderer2D> getRenderer() { return m_renderer; }
		inline QSharedPointer<OrthographicCamera> getCamera() { return m_camera; }

	private:
		QSharedPointer<OrthographicCamera> m_camera;
		QSharedPointer<BatchRenderer2D> m_renderer;

		QVector<QSharedPointer<Entity>> m_entities;
	};
}

#endif

