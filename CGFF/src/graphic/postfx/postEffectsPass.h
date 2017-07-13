#ifndef POST_EFFECTS_PASS_H
#define POST_EFFECTS_PASS_H

#include "utils/qtopengl.h"
#include "graphic/meshFactory.h"
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QSharedPointer>
#include <QSize>

namespace CGFF {
    class PostEffectsPass
    {

    public:
        PostEffectsPass(const QSharedPointer<QOpenGLShaderProgram>& shaderProgram, QSize& size);
        virtual~PostEffectsPass();

        void RenderPass(const QSharedPointer<QOpenGLFramebufferObject>& target);

    private:
        QSharedPointer<QOpenGLShaderProgram> m_shaderProgram;
        QSize m_size;
    };
}

#endif
