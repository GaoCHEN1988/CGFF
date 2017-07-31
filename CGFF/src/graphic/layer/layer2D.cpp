#include "layer2D.h"

namespace CGFF {

    Layer2D::Layer2D(QSharedPointer<Renderer2D> renderer, QSharedPointer<QOpenGLShaderProgram>  shader, QMatrix4x4 projectionMatrix)
        : Layer()
        , m_renderer(renderer)
        , m_shader(shader)
        , m_projectionMatrix(projectionMatrix)
    {
        m_shader->bind();
        m_shader->setUniformValue("projMatrix", m_projectionMatrix);
        GLint texIDs[] =
        {
            0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
            11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
            22, 23, 24, 25, 26, 27, 28, 29, 30, 31
        };
        m_shader->setUniformValueArray("textures", texIDs, 32);

        m_shader->release();
    }

    Layer2D::~Layer2D()
    {
    }

    void Layer2D::add(QSharedPointer<Renderable2D> renderable)
    {
        m_renderables.push_back(renderable);
    }

    QSharedPointer<Renderable2D> Layer2D::submit(QSharedPointer<Renderable2D> renderable)
    {
        m_submittedRenderables.push_back(renderable);
        return renderable;
    }

    void Layer2D::render()
    {
        m_shader->bind();
        m_shader->setUniformValue("projMatrix", m_projectionMatrix);

        m_renderer->begin();
        for (const QSharedPointer<Renderable2D> r : m_renderables)
        {
            r->submit(m_renderer);
        }

        for (const QSharedPointer<Renderable2D> renderable : m_submittedRenderables)
            renderable->submit(m_renderer);

        m_renderer->end();
        m_renderer->flush();

        render(m_renderer);
        m_submittedRenderables.clear();

        m_shader->release();
    }

    void Layer2D::resize(int width, int height)
    {
        m_projectionMatrix.setToIdentity();
        m_projectionMatrix.perspective(45.0f, GLfloat(width) / height, 0.0f, 100.0f);
    }
}