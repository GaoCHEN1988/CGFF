#ifndef POST_EFFECTS_H
#define POST_EFFECTS_H

#include "graphic/api/framebuffer.h"
#include "graphic/api/vertexArray.h"
#include "graphic/api/indexBuffer.h"
#include "postEffectsPass.h"

namespace CGFF {
    class PostEffects
    {
    
    public:
        PostEffects();
        virtual~PostEffects();
        void push(QSharedPointer<PostEffectsPass> pass);
        void pop();

        void renderPostEffects(const QSharedPointer<Framebuffer>& source, const QSharedPointer<Framebuffer>& target, VertexArray* quad, IndexBuffer* indices);

    private:
        QVector<QSharedPointer<PostEffectsPass>> m_Passes;
    };
}
#endif