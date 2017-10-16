#pragma once

#include "learnOpenglHeader.h"
#include "learnGLMeshFactory.h"

namespace LearnGL {

    class DeferredShading
    {
    public:
        DeferredShading(const QSharedPointer<CGFF::Scene>& scene);
        ~DeferredShading();

        void init();
        void render();


    private:
        QSharedPointer<CGFF::Scene> m_scene;
        QSharedPointer<CGFF::Model> m_objectModel;
        QSharedPointer<CGFF::MaterialInstance> m_lightBoxMaterial;
    };

}