#ifndef LAYER_2D_H
#define LAYER_2D_H

#include "layer.h"
#include "graphic/renderer2d.h"
#include "graphic/renderable2d.h"
#include "graphic/batchRenderer2d.h"

#include <QOpenGLShaderProgram>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

namespace CGFF {
    class Layer2D : public Layer
    {
    public:
        Layer2D(QSharedPointer<Renderer2D> renderer, QSharedPointer<QOpenGLShaderProgram> shader, QMatrix4x4 projectionMatrix = QMatrix4x4());
        virtual ~Layer2D();
        virtual void render() override;
        virtual void render(QSharedPointer<Renderer2D>& renderer) {};
        virtual void resize(int width, int height) override;
        virtual void add(QSharedPointer<Renderable2D> renderable);
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
        QSharedPointer<QOpenGLShaderProgram> m_shader;
        QSharedPointer<Renderer2D> m_renderer;
        QVector<QSharedPointer<Renderable2D>> m_renderables;
        QVector<QSharedPointer<Renderable2D>> m_submittedRenderables;
        QMatrix4x4 m_projectionMatrix;
    };
}



#endif
