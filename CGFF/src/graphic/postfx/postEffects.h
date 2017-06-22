#ifndef POST_EFFECTS_H
#define POST_EFFECTS_H

#include "postEffectsPass.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector>

namespace CGFF {
    class PostEffects
    {
    
    public:
        PostEffects();
        ~PostEffects();
        void push(QSharedPointer<PostEffectsPass> pass);
        void pop();

        void renderPostEffects(const QSharedPointer<QOpenGLFramebufferObject>& source, const QSharedPointer<QOpenGLFramebufferObject>& target, QOpenGLVertexArrayObject& quad, QOpenGLBuffer* indices);

    private:
        QVector<QSharedPointer<PostEffectsPass>> m_Passes;
    };
}
#endif