#include "glVertexBuffer.h"
#include "utils/qtopengl.h"

namespace CGFF {

    static QOpenGLBuffer::UsagePattern toGlUsagePattern(BufferUsage usage)
    {
        switch (usage)
        {
        case BufferUsage::STATIC: 
            return QOpenGLBuffer::StaticDraw;

        case BufferUsage::DYNAMIC: 
            return QOpenGLBuffer::DynamicDraw;
        }
        return QOpenGLBuffer::DynamicDraw;
    }

    GLVertexBuffer::GLVertexBuffer(BufferUsage usage)
        : m_usage(usage)
        , m_glVertexBuffer(QOpenGLBuffer::VertexBuffer)
        , m_size(0)
    {
        m_glVertexBuffer.create();
    }

    GLVertexBuffer::~GLVertexBuffer()
    {
        m_glVertexBuffer.destroy();
    }

    void GLVertexBuffer::resize(uint size)
    {
        m_size = size;
        m_glVertexBuffer.bind();
        m_glVertexBuffer.setUsagePattern(toGlUsagePattern(m_usage));
        m_glVertexBuffer.allocate(NULL, m_size);
    }

    void GLVertexBuffer::setLayout(const LayoutBuffer& layoutbuffer)
    {
        m_layout = layoutbuffer;
        const QVector<BufferElement>& layout = layoutbuffer.getLayout();
        for (uint i = 0; i < layout.size(); i++)
        {
            const BufferElement& element = layout[i];
            GL->glEnableVertexAttribArray(i);
            GL->glVertexAttribPointer(i, element.count, element.type, element.normalized, layoutbuffer.getStride(), (const void*)element.offset);
        }
    }

    void GLVertexBuffer::setData(uint size, const void* data)
    {
        m_size = size;
        m_glVertexBuffer.bind();
        m_glVertexBuffer.setUsagePattern(toGlUsagePattern(m_usage));
        m_glVertexBuffer.allocate(data, m_size);
    }

    void GLVertexBuffer::releasePointer()
    {
        m_glVertexBuffer.unmap();
    }

    void GLVertexBuffer::bind()
    {
        m_glVertexBuffer.bind();
        //test, need to be considered
        //setLayout(m_layout);
    }

    void GLVertexBuffer::unBind()
    {
        m_glVertexBuffer.release();
    }

    void* GLVertexBuffer::getPointerInternal()
    {
        return m_glVertexBuffer.map(QOpenGLBuffer::WriteOnly);
    }
}