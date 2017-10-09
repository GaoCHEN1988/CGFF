#pragma once

#include "learnOpenglHeader.h"
#include "learnGLMeshFactory.h"

namespace LearnGL {

    class PointShadows
    {
    public:
        PointShadows(const QSharedPointer<CGFF::Scene>& scene);
        ~PointShadows();

        void init();
        void render();


    private:

        QSharedPointer<CGFF::Entity> m_plane;
        QSharedPointer<CGFF::Entity> m_cube;
        QSharedPointer<CGFF::Entity> m_cube2;
        QSharedPointer<CGFF::Entity> m_cube3;
        QSharedPointer<CGFF::MaterialInstance> m_objectMaterialInstance;
        QSharedPointer<CGFF::MaterialInstance> m_depthMaterialInstance;
        QSharedPointer<CGFF::MaterialInstance> m_skyboxMaterial;
        QSharedPointer<CGFF::LightSetup> m_lights;

        QSharedPointer<CGFF::FramebufferDepth> m_depthmap;

        QSharedPointer<CGFF::Scene> m_scene;
    };

}
