#ifndef LAYER_2D_H
#define LAYER_2D_H

#include "layer.h"
#include "graphic/renderer2d.h"
#include "graphic/renderable2d.h"
#include "../mask.h"
#include "../batchRenderer2d.h"

namespace CGFF {
    class Layer2D : public Layer
    {
    public:
        Layer2D(QSharedPointer<Renderer2D> renderer, QMatrix4x4 projectionMatrix = QMatrix4x4(), QObject *parent = Q_NULLPTR);
        virtual ~Layer2D();

		virtual void init();
		virtual void init(QSharedPointer<Renderer2D> renderer, QSharedPointer<Material> material);

        virtual void render() override;
        virtual void render(QSharedPointer<Renderer2D>& renderer) {};
		virtual void resize(int width, int height) override;
		virtual void closeEvent(QEvent *event) override;

        virtual void add(QSharedPointer<Renderable2D> renderable);
		inline const QVector<QSharedPointer<Renderable2D>>& getRenderables() const { return m_renderables; }

        virtual QSharedPointer<Renderable2D> submit(QSharedPointer<Renderable2D> renderable);
        inline void setMask(QSharedPointer<CGFF::Mask> mask)
        {
            m_renderer->setMask(mask);
        }
        inline QSharedPointer<Renderer2D> getRenderer()
        {
            return m_renderer;
        }
    protected:
        QSharedPointer<Material> m_material;
        QSharedPointer<Renderer2D> m_renderer;
        QVector<QSharedPointer<Renderable2D>> m_renderables;
        QVector<QSharedPointer<Renderable2D>> m_submittedRenderables;
        QMatrix4x4 m_projectionMatrix;
    };
}



#endif
