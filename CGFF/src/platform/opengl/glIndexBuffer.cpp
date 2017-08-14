#include "glIndexBuffer.h"

namespace CGFF {

    GLIndexBuffer::GLIndexBuffer(uint* data, uint count)
        : m_count(count)
        , m_glIndexBuffer(QOpenGLBuffer::IndexBuffer)
    {
       m_glIndexBuffer.create();
       m_glIndexBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
       m_glIndexBuffer.bind();
       m_glIndexBuffer.allocate(data, count* sizeof(uint));

       //test
       m_glIndexBuffer.release();
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        m_glIndexBuffer.destroy();
    }

    void GLIndexBuffer::bind() 
    {
        m_glIndexBuffer.bind();
    }
    void GLIndexBuffer::unBind()
    {
        m_glIndexBuffer.release();
    }

    uint GLIndexBuffer::getCount() const
    {
        return m_count;
    }

}