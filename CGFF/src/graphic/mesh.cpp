#include "mesh.h"

namespace CGFF {

    Mesh::Mesh(const QSharedPointer<VertexArray>& vertexArray,
        const QSharedPointer<IndexBuffer>& indexBuffer,
        const QSharedPointer<MaterialInstance>& materialInstance,
        const QVector<MeshTexture>& textures,
        DrawMode mode) 
        : m_vertexArray(vertexArray)
        , m_indexBuffer(indexBuffer)
        , m_materialInstance(materialInstance)
        , m_textures(textures)
		, m_drawMode(mode)
    {
    }

	Mesh::Mesh(QSharedPointer<Mesh> mesh, DrawMode mode)
		: m_vertexArray(mesh->m_vertexArray)
		, m_indexBuffer(mesh->m_indexBuffer)
		, m_materialInstance(mesh->m_materialInstance)
        , m_textures(mesh->m_textures)
		, m_drawMode(mode)
	{
	}

    Mesh::~Mesh()
    {
    }

    void Mesh::render(Renderer3D& renderer)
    {
        uint diffuseNr = 1;
        uint specularNr = 1;
        uint normalNr = 1;
        uint heightNr = 1;

        for (int i = 0; i < m_textures.size(); i++)
        {
            QString name = m_textures[i].type;
            if (name == pbr_diffuseMap)
                name += QString::number(diffuseNr++);
            else if (name == pbr_specularMap)
                name += QString::number(specularNr++);
            else if (name == pbr_normalMap)
                name += QString::number(normalNr++);
            else if (name == pbr_heightMap)
                name += QString::number(heightNr++);

            m_materialInstance->setTexture(name, m_textures[i].texture);
        }

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