#ifndef LAYER_3D_H
#define LAYER_3D_H

#include "layer.h"
#include "graphic/scene.h"
#include "graphic/renderer/renderer3d.h"
#include "graphic/renderer/forwardRenderer.h"

namespace CGFF {

    class Layer3D : public Layer
    {
    public:
        Layer3D(QSharedPointer<Scene> scene, QSharedPointer<Renderer3D> renderer, QWidget *parent = Q_NULLPTR);
        virtual ~Layer3D();

        virtual void init() override;
		virtual void render() override;
		virtual void render(QSharedPointer<Renderer3D>& renderer) {};
		void resizeEvent(QResizeEvent *event) override;
		virtual void closeEvent(QCloseEvent *event) override;

        inline QSharedPointer<Scene>& getScene() { return m_scene; }

    protected:
        QSharedPointer<Scene> m_scene;
        QSharedPointer<Renderer3D> m_renderer;
    };

}
#endif
