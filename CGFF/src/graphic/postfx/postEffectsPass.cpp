#include "postEffectsPass.h"
namespace CGFF {

	struct PostEffectsPassShader
	{
		QMatrix4x4 pr_matrix;
		QSharedPointer<Texture> texture;
	};

    PostEffectsPass::PostEffectsPass(const QSharedPointer<Shader>& shader, QSize& size)
        : m_material(QSharedPointer<Material>(new Material(shader)))
        , m_size(size)
    {

    }
    PostEffectsPass::~PostEffectsPass()
    {
    }

    void PostEffectsPass::renderPass(const QSharedPointer<Framebuffer>& target)
    {
		QMatrix4x4 proj;
		proj.ortho(0, (float)target->getWidth(), (float)target->getHeight(), 0, -1.0f, 100.0f);
		m_material->setUniform("pr_matrix", proj);
		m_material->bind();

		//Test
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		m_material->unbind();
    }
}