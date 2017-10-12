#include "postEffectsPass.h"
namespace CGFF {

	struct PostEffectsPassShader
	{
		QMatrix4x4 pr_matrix;
		QSharedPointer<Texture> texture;
	};

    PostEffectsPass::PostEffectsPass(const QSharedPointer<Shader>& shader, QSize& size)
        : m_material(nullptr)
        , m_size(size)
    {
        m_material = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(shader))));
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

    void PostEffectsPass::renderPass(const QSharedPointer<Framebuffer>& source, const QSharedPointer<Mesh>& mesh)
    {
		m_material->bind();

        m_material->setTexture("tex", source->getTexture());

        mesh->draw();

		m_material->unbind();
    }
}