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

    void PostEffectsPass::bind()
    {
        m_material->bind();
    }
    void PostEffectsPass::unBind()
    {
        m_material->unbind();
    }

    void PostEffectsPass::setSize(QSize size)
    {
        QMatrix4x4 proj;
        proj.ortho(0, (float)size.width(), (float)size.height(), 0, -1.0f, 100.0f);
        m_material->setUniform("projMatrix", proj);
    }


    void PostEffectsPass::renderPass(const QSharedPointer<Framebuffer>& target, const QSharedPointer<Mesh>& mesh)
    {
		QMatrix4x4 proj;
		proj.ortho(0, (float)target->getWidth(), (float)target->getHeight(), 0, -1.0f, 100.0f);
        m_material->setUniform("projMatrix", proj);
        m_material->setTexture("tex", 0);
		m_material->bind();

        mesh->draw();

		m_material->unbind();
    }
}