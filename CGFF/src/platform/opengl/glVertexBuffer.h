#ifndef CGFF_GL_VERTEX_BUFFER_H
#define CGFF_GL_VERTEX_BUFFER_H

#include "graphic/api/vertexBuffer.h"
#include <QOpenGLBuffer>

namespace CGFF {

    class GLVertexBuffer : public VertexBuffer
    {
    public:
        GLVertexBuffer(BufferUsage usage);
        virtual ~GLVertexBuffer();

        void resize(uint size) override;
        void setLayout(const LayoutBuffer& layoutbuffer) override;
        void setData(uint size, const void* data) override;

        void releasePointer() override;

        void bind() override;
        void unBind() override;
    protected:
        void* getPointerInternal() override;

    private:
        QOpenGLBuffer m_glVertexBuffer;
        BufferUsage m_usage;
        uint m_size;
        LayoutBuffer m_layout;
    };
}

#endif