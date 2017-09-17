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
        Layer2D(QSize size, QWidget *parent = Q_NULLPTR, QMatrix4x4 projectionMatrix = QMatrix4x4());
		Layer2D(QSharedPointer<Scene2D> scene, QWidget *parent = Q_NULLPTR);
        virtual ~Layer2D();

        virtual void render() override;
		virtual void render(QSharedPointer<Renderer2D>& renderer) {};
		//virtual void resize(int width, int height) override;
		void resizeEvent(QResizeEvent *event) override;
		virtual void closeEvent(QCloseEvent *event) override;

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
            return m_scene2D->getRenderer();
        }
    protected:
        QSharedPointer<Material> m_material;
		QSharedPointer<Renderer2D> m_renderer;
		QSharedPointer<Scene2D> m_scene2D;
        QVector<QSharedPointer<Renderable2D>> m_submittedRenderables;
		QSize m_size;
    };
}



#endif
