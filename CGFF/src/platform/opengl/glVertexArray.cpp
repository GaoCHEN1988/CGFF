#include "glVertexArray.h"
#include "utils/qtopengl.h"

namespace CGFF {

    GLVertexArray::GLVertexArray()
    {
        m_glVertexArray.create();
    }

    GLVertexArray::~GLVertexArray()
    {

    }

    void GLVertexArray::pushBuffer(QSharedPointer<VertexBuffer> buffer)
    {
        m_buffers.push_back(buffer);
    }

    void GLVertexArray::bind()
    {
        m_glVertexArray.bind();
    }

    void GLVertexArray::unBind()
    {
        m_glVertexArray.release();
    }

    void GLVertexArray::draw(uint count) const 
    {
        GL->glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
    }

}