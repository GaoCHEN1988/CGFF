#ifndef SCENE_H
#define SCENE_H

#include "renderer3d.h"
#include "entity/entity.h"
#include "camera/camera.h"

namespace CGFF {

    class Scene
    {
    private:
        QVector<QSharedPointer<Entity>> m_entities;
        QSharedPointer<Camera> m_camera;
    public:
        Scene();
        Scene(QSharedPointer<Camera>& camera);
        ~Scene();
        void add(QSharedPointer<Entity>& entity);
        void render(QSharedPointer<Renderer3D>& renderer);

        const QVector<QSharedPointer<Entity>>& getEntities() const { return m_entities; }
    };
}
#endif
