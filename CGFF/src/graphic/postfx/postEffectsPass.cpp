#include "postEffectsPass.h"
namespace CGFF {

    PostEffectsPass::PostEffectsPass(const QSharedPointer<QOpenGLShaderProgram>& shaderProgram, QSize& size)
        : m_shaderProgram(shaderProgram)
        , m_size(size)
    {
        m_shaderProgram->bind();
        QMatrix4x4 proj = QMatrix4x4();
        proj.ortho(0, m_size.width(), m_size.height(), 0, -1.0f, 1.0f);
        m_shaderProgram->setUniformValue("projMatrix", proj);
        m_shaderProgram->setUniformValue("tex", 0);
        m_shaderProgram->release();

    }
    PostEffectsPass::~PostEffectsPass()
    {
    }

    void PostEffectsPass::RenderPass(const QSharedPointer<QOpenGLFramebufferObject>& target)
    {
        m_shaderProgram->bind();
        GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        m_shaderProgram->release();
    }
}