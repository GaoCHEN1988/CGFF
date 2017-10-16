#pragma once

#include "learnOpenglHeader.h"
#include "learnGLMeshFactory.h"

namespace LearnGL {

    class PBR
    {
    public:
        PBR(const QSharedPointer<CGFF::Scene>& scene);
        ~PBR();

        void init();
        void render();


    private:
        QSharedPointer<CGFF::Scene> m_scene;
        QSharedPointer<CGFF::Mesh> m_sphereMesh;
        QSharedPointer<CGFF::Model> m_sphereModel;
    };

}