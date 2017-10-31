#ifndef CGFF_SCENE_H
#define CGFF_SCENE_H

#include "renderer/renderer3d.h"
#include "entity/entity.h"
#include "camera/camera.h"
#include "camera/mayaCamera.h"
#include "camera/fpsCamera.h"
#include "resource/resourceManager.h"

namespace CGFF {

    class Scene
    {
    public:
        Scene(QSize size, const QString& name = "Scene3D");
        Scene(QSharedPointer<Camera>& camera, const QString& name = "Scene3D");
        virtual~Scene();
        void add(const QString& name, const QSharedPointer<Entity>& entity);
        void add(const QString& name, const QSharedPointer<Light>& light);
        void render(QSharedPointer<Renderer3D>& renderer);
        void setCamera(const QSharedPointer<Camera>& camera);
        void setSkyBox(const QSharedPointer<Entity>& skyBox, const QSharedPointer<Texture>& environment);
		void close();
   
        inline const QSharedPointer<Camera>& getCamera() const { return m_camera; }
        inline QSize getSize() const { return m_size; }
        inline QString getName() const { return m_name; }

    private:
        void initSceneResource();

    private:
        //QVector<QSharedPointer<Entity>> m_entities;
        QSharedPointer<Camera> m_camera;
        //QSharedPointer<LightSetup> m_lightSetup;
        //QVector<QSharedPointer<LightSetup>> m_lightSetupStack;
        //QSharedPointer<Entity> m_skyBox;
        //QSharedPointer<Texture> m_environment;
		QSize m_size;
        QString m_name;
        QSharedPointer<SceneResource> m_resource;
    };
}
#endif
