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
        m_material->bind();
        QMatrix4x4 proj;
        proj.ortho(0, (float)m_size.width(), (float)m_size.height(), 0, -1.0f, 100.0f);
        m_material->setUniform("projectionMatrix", proj);
        m_material->unbind();
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
        proj.ortho(0, (float)m_size.width(), (float)m_size.height(), 0, -1.0f, 100.0f);
        m_material->setUniform("projectionMatrix", proj);
    }


    void PostEffectsPass::renderPass(const QSharedPointer<Framebuffer>& source, const QSharedPointer<Mesh>& mesh)
    {
		m_material->bind();

        m_material->setTexture("tex", source->getTexture());

        mesh->draw();

		m_material->unbind();
    }
}