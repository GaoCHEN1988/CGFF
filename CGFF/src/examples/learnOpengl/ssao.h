#pragma once

#include "learnOpenglHeader.h"
#include "learnGLMeshFactory.h"

namespace LearnGL {

    class SSAO
    {
    public:
        SSAO(const QSharedPointer<CGFF::Scene>& scene);
        ~SSAO();

        void init();
        void render();


    private:
        QSharedPointer<CGFF::Scene> m_scene;
        QSharedPointer<CGFF::Model> m_objectModel;
        QSharedPointer<CGFF::Entity> m_cube;
    };

}