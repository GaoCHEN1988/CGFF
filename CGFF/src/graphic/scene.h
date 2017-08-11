#ifndef CGFF_SCENE_H
#define CGFF_SCENE_H

#include "renderer3d.h"
#include "entity/entity.h"
#include "camera/camera.h"

namespace CGFF {

    class Scene
    {
    public:
        Scene();
        Scene(QSharedPointer<Camera>& camera);
        virtual~Scene();
        void add(QSharedPointer<Entity>& entity);
        void pushLightSetup(QSharedPointer<LightSetup>& lightSetup);
        QSharedPointer<LightSetup> popLightSetup();
        void render(QSharedPointer<Renderer3D>& renderer);
   
        inline const QSharedPointer<Camera>& getCamera() const { return m_camera; }
        inline const QVector<QSharedPointer<Entity>>& getEntities() const { return m_entities; }

    private:
        QVector<QSharedPointer<Entity>> m_entities;
        QSharedPointer<Camera> m_camera;
        QVector<QSharedPointer<LightSetup>> m_lightSetupStack;
    };
}
#endif
