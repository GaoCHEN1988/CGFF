#ifndef CGFF_SCENE_H
#define CGFF_SCENE_H

#include "renderer/renderer3d.h"
#include "entity/entity.h"
#include "camera/camera.h"
#include "camera/mayaCamera.h"
#include "camera/fpsCamera.h"

namespace CGFF {

    class Scene
    {
    public:
        Scene(QSize size);
        Scene(QSharedPointer<Camera>& camera);
        virtual~Scene();
        void add(const QSharedPointer<Entity>& entity);
        void add(const QSharedPointer<Light>& light);
        void pushLightSetup(QSharedPointer<LightSetup>& lightSetup);
        QSharedPointer<LightSetup> popLightSetup();
        void render(QSharedPointer<Renderer3D>& renderer);
        void setCamera(const QSharedPointer<Camera>& camera);
        void setSkyBox(const QSharedPointer<Entity>& skyBox, const QSharedPointer<Texture>& environment);
		void close();
   
        inline const QSharedPointer<Camera>& getCamera() const { return m_camera; }
        inline const QVector<QSharedPointer<Entity>>& getEntities() const { return m_entities; }
        inline QSize getSize() const { return m_size; }

    private:
        QVector<QSharedPointer<Entity>> m_entities;
        QSharedPointer<Camera> m_camera;
        QSharedPointer<LightSetup> m_lightSetup;
        QVector<QSharedPointer<LightSetup>> m_lightSetupStack;
        QSharedPointer<Entity> m_skyBox;
        QSharedPointer<Texture> m_environment;
		QSize m_size;
    };
}
#endif
