#ifndef LAYER_3D_H
#define LAYER_3D_H

#include "graphic/scene.h"
#include "graphic/renderer3d.h"
#include "graphic/forwardRenderer.h"

namespace CGFF {

    class Layer3D
    {
    public:
        Layer3D(QSharedPointer<Scene> scene);
        ~Layer3D();

        virtual void init();

        inline QSharedPointer<Scene>& GetScene() { return m_scene; }

        void render();

    protected:
        QSharedPointer<Scene> m_scene;
        QSharedPointer<Renderer3D> m_renderer;
    };

}
#endif
