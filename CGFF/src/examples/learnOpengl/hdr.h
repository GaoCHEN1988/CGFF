#pragma once

#include "learnOpenglHeader.h"
#include "learnGLMeshFactory.h"

namespace LearnGL {

    class HDR
    {
    public:
        HDR(const QSharedPointer<CGFF::Scene>& scene);
        ~HDR();

        void init();
        void render();


    private:
        QSharedPointer<CGFF::Scene> m_scene;

        QSharedPointer<CGFF::Entity> m_cube;
        QSharedPointer<CGFF::MaterialInstance> m_objectMaterialInstance;
    };

}