#pragma once

#include "learnOpenglHeader.h"
#include "learnGLMeshFactory.h"

namespace LearnGL {

    class ParallaxMapping
    {
    public:
        ParallaxMapping(const QSharedPointer<CGFF::Scene>& scene);
        ~ParallaxMapping();

        void init();
        void render();


    private:
        QSharedPointer<CGFF::Scene> m_scene;

        QSharedPointer<CGFF::Entity> m_plane;
        QSharedPointer<CGFF::MaterialInstance> m_objectMaterialInstance;
    };

}