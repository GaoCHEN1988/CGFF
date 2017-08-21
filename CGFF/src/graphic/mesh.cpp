#include "mesh.h"

namespace CGFF {

    Mesh::Mesh(QSharedPointer<VertexArray> vertexArray, QSharedPointer<IndexBuffer> indexBuffer, QSharedPointer<MaterialInstance> materialInstance)
        : m_vertexArray(vertexArray)
        , m_indexBuffer(indexBuffer)
        , m_materialInstance(materialInstance)
    {
    }

	Mesh::Mesh(QSharedPointer<Mesh> mesh)
		: m_vertexArray(mesh->m_vertexArray)
		, m_indexBuffer(mesh->m_indexBuffer)
		, m_materialInstance(mesh->m_materialInstance)
	{
	}

    Mesh::~Mesh()
    {
    }

    void Mesh::render(Renderer3D& renderer)
    {
        m_materialInstance->bind();

        m_vertexArray->bind();
        m_indexBuffer->bind();
        m_vertexArray->draw(m_indexBuffer->getCount());
        m_indexBuffer->unBind();
        m_vertexArray->unBind();

        m_materialInstance->unbind();
    }
}