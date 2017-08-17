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
        m_Passes.push_back(pass);
    }

    void PostEffects::pop()
    {
        m_Passes.pop_back();
    }

    void PostEffects::renderPostEffects(const QSharedPointer<Framebuffer>& source, const QSharedPointer<Framebuffer>& target, VertexArray* quad, IndexBuffer* indices)
    {
        target->bind();
        quad->bind();
        indices->bind();

        for (QSharedPointer<PostEffectsPass> pass : m_Passes)
            pass->renderPass(target);

        indices->unBind();
        quad->unBind();
        target->unBind();
    }
}