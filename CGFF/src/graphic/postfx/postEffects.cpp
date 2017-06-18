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

    void PostEffects::renderPostEffects(const QSharedPointer<QOpenGLFramebufferObject>& source, const QSharedPointer<QOpenGLFramebufferObject>& target, QOpenGLVertexArrayObject& quad, QOpenGLBuffer* indices)
    {
        target->bind();
        GL->glActiveTexture(GL_TEXTURE0);
        GL->glBindTexture(GL_TEXTURE_2D, source->texture());
        quad.bind();
        indices->bind();

        for (QSharedPointer<PostEffectsPass> pass : m_Passes)
            pass->RenderPass(target);

        indices->release();
        quad.release();
        target->release();
    }
}