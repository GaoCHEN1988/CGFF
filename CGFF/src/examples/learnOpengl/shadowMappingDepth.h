#pragma once

#include "learnOpenglHeader.h"
#include "learnGLMeshFactory.h"

namespace LearnGL {

    class ShadowMappingDepth
    {
    public:
        ShadowMappingDepth(const QSharedPointer<CGFF::Scene>& scene);
        ~ShadowMappingDepth();

        void init();
        void render();


    private:
        QVector<QSharedPointer<CGFF::Entity>> m_Spheres;
        QSharedPointer<CGFF::Entity> m_plane;
        QSharedPointer<CGFF::Entity> m_cube;
        QSharedPointer<CGFF::Entity> m_cube2;
        QSharedPointer<CGFF::MaterialInstance> m_objectMaterialInstance;
        QSharedPointer<CGFF::MaterialInstance> m_depthMaterialInstance;
        QSharedPointer<CGFF::MaterialInstance> m_skyboxMaterial;
        QSharedPointer<CGFF::LightSetup> m_lights;

        QSharedPointer<CGFF::FramebufferDepth> m_depthmap;

        QSharedPointer<CGFF::Scene> m_scene;
    };

}



