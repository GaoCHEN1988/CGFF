#pragma once

#include "learnOpenglHeader.h"
#include "learnGLMeshFactory.h"

namespace LearnGL {

    class NormalMapping
    {
    public:
        NormalMapping(const QSharedPointer<CGFF::Scene>& scene);
        ~NormalMapping();

        void init();
        void render();


    private:
        QSharedPointer<CGFF::Scene> m_scene;

        QSharedPointer<CGFF::Entity> m_plane;
        QSharedPointer<CGFF::MaterialInstance> m_objectMaterialInstance;
    };

}