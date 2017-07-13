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
        virtual~Scene();
        void add(QSharedPointer<Entity>& entity);
        void render(QSharedPointer<Renderer3D>& renderer);
   
        inline const QSharedPointer<Camera>& getCamera() const { return m_camera; }
        inline const QVector<QSharedPointer<Entity>>& getEntities() const { return m_entities; }
    };
}
#endif
