#ifndef LAYER_3D_H
#define LAYER_3D_H

#include "layer.h"
#include "graphic/scene.h"
#include "graphic/renderer3d.h"
#include "graphic/forwardRenderer.h"

namespace CGFF {

    class Layer3D : public Layer
    {
    public:
        Layer3D(QSharedPointer<Scene> scene, QSharedPointer<Renderer3D> renderer = QSharedPointer<Renderer3D>(new ForwardRenderer()));
        virtual ~Layer3D();

        virtual void init() override;
		virtual void render() override;
		virtual void resize(int width, int height) override;

        inline QSharedPointer<Scene>& getScene() { return m_scene; }

    protected:
        QSharedPointer<Scene> m_scene;
        QSharedPointer<Renderer3D> m_renderer;
    };

}
#endif
