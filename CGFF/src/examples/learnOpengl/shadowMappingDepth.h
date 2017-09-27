#pragma once

#include "learnOpenglHeader.h"

namespace LearnGL {

    class ShadowMappingDepth
    {
    public:
        ShadowMappingDepth();
        ~ShadowMappingDepth();

        void init(QSize size);
        void render();


    private:
        QVector<QSharedPointer<CGFF::Entity>> m_Spheres;
        QSharedPointer<CGFF::Entity> m_plane;
        QSharedPointer<CGFF::Entity> m_dagger;
        QSharedPointer<CGFF::Entity> m_cube;
        QSharedPointer<CGFF::MaterialInstance> m_skyboxMaterial;
        QSharedPointer<CGFF::LightSetup> m_lights;

        QSharedPointer<CGFF::FramebufferDepth> m_depthmap;
    };

}



