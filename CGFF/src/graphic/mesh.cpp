#include "mesh.h"

namespace CGFF {

    Mesh::Mesh(QOpenGLVertexArrayObject* vertexArray, QOpenGLBuffer* indexBuffer, QSharedPointer<MaterialInstance> materialInstance)
        : m_vertexArray(vertexArray)
        , m_indexBuffer(indexBuffer)
        , m_materialInstance(materialInstance)
    {
    }

    Mesh::~Mesh()
    {
        ////To be considered
        //delete m_vertexArray;
        //delete m_indexBuffer;
        //delete m_materialInstance;
    }

    void Mesh::render(Renderer3D& renderer)
    {
        //m_materialInstance->getMaterial()->bind();
        m_materialInstance->bind();

        m_vertexArray->bind();
        m_indexBuffer->bind();
        //m_vertexArray->Draw(m_IndexBuffer->GetCount());
        //Test QOpenGLBuffer size()
        // To do: set value of count some where!!!
        GL->glDrawElements(GL_TRIANGLES, m_indexBuffer->size() / sizeof(uint), GL_UNSIGNED_INT, NULL);
        m_indexBuffer->release();
        m_vertexArray->release();

        m_materialInstance->unbind();
    }
}