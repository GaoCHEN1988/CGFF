#ifndef POST_EFFECTS_PASS_H
#define POST_EFFECTS_PASS_H

#include "../utils/qtopengl.h"
#include "../meshFactory.h"
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QSharedPointer>
#include <QSize>

namespace CGFF {
    class PostEffectsPass/*: protected QOpenGLFunctions_4_4_Core*/
    {

    public:
        PostEffectsPass(const QSharedPointer<QOpenGLShaderProgram>& shaderProgram, QSize& size);
        ~PostEffectsPass();

        void RenderPass(const QSharedPointer<QOpenGLFramebufferObject>& target);

    private:
        QSharedPointer<QOpenGLShaderProgram> m_shaderProgram;
        QSize m_size;
        MeshFactory::Quad m_quad;
    };
}

#endif
