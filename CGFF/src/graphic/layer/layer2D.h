#ifndef LAYER_2D_H
#define LAYER_2D_H

#include "layer.h"
#include "../mask.h"
#include "graphic/renderer/batchRenderer2d.h"
#include "graphic/scene2D.h"

namespace CGFF {
    class Layer2D : public Layer
    {
    public:
        Layer2D(QMatrix4x4 projectionMatrix = QMatrix4x4(), QObject *parent = Q_NULLPTR);
		Layer2D(QSharedPointer<Scene2D> scene, QObject *parent = Q_NULLPTR);
        virtual ~Layer2D();

		virtual void init() override;
        virtual void render() override;
		virtual void render(QSharedPointer<Renderer2D>& renderer) {};
		virtual void resize(int width, int height) override;
		virtual void closeEvent(QEvent *event) override;

		virtual void add(QSharedPointer<Sprite> sprite);
		inline QSharedPointer<Scene2D> getScene() { return m_scene2D; }

        virtual QSharedPointer<Renderable2D> submit(QSharedPointer<Renderable2D> renderable);
        inline void setMask(QSharedPointer<CGFF::Mask> mask)
        {
			m_scene2D->getRenderer()->setMask(mask);
            m_renderer->setMask(mask);
        }
        inline QSharedPointer<Renderer2D> getRenderer()
        {
            return m_renderer;
        }
    protected:
        QSharedPointer<Material> m_material;
		QSharedPointer<Renderer2D> m_renderer;
		QSharedPointer<Scene2D> m_scene2D;
        QVector<QSharedPointer<Renderable2D>> m_submittedRenderables;
    };
}



#endif
