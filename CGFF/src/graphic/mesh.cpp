#include "mesh.h"

namespace CGFF {

    Mesh::Mesh(QSharedPointer<VertexArray> vertexArray, QSharedPointer<IndexBuffer> indexBuffer, QSharedPointer<MaterialInstance> materialInstance, DrawMode mode)
        : m_vertexArray(vertexArray)
        , m_indexBuffer(indexBuffer)
        , m_materialInstance(materialInstance)
		, m_drawMode(mode)
    {
    }

	Mesh::Mesh(QSharedPointer<Mesh> mesh, DrawMode mode)
		: m_vertexArray(mesh->m_vertexArray)
		, m_indexBuffer(mesh->m_indexBuffer)
		, m_materialInstance(mesh->m_materialInstance)
		, m_drawMode(mode)
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
        m_vertexArray->draw(m_indexBuffer->getCount(), m_drawMode);
        m_indexBuffer->unBind();
        m_vertexArray->unBind();

        m_materialInstance->unbind();
    }

    void Mesh::bind() 
    {
        m_vertexArray->bind();
        m_indexBuffer->bind();
    }
    void Mesh::unBind()
    {
        m_indexBuffer->unBind();
        m_vertexArray->unBind();
    }
    void Mesh::draw()
    {
        m_vertexArray->draw(m_indexBuffer->getCount(), m_drawMode);
    }

}