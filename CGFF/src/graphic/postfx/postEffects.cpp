#include "postEffects.h"

namespace CGFF {

    PostEffects::PostEffects()
    {
    }

    PostEffects::~PostEffects()
    {

    }

    void PostEffects::push(QSharedPointer<PostEffectsPass> pass)
    {
        m_passes.push_back(pass);
    }

    void PostEffects::pop()
    {
        m_passes.pop_back();
    }

    void PostEffects::renderPostEffects(const QSharedPointer<Framebuffer>& source, const QSharedPointer<Framebuffer>& target, QSharedPointer<VertexArray> quad, QSharedPointer<IndexBuffer> indices)
    {
        target->bind();
        quad->bind();
        indices->bind();

        for (QSharedPointer<PostEffectsPass> pass : m_passes)
            pass->renderPass(target);

        indices->unBind();
        quad->unBind();
        target->unBind();
    }
}