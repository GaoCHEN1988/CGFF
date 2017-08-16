#ifndef CGFF_VERTEX_BUFFER_H
#define CGFF_VERTEX_BUFFER_H

#include "layoutBuffer.h"

namespace CGFF {

    enum class BufferUsage
    {
        STATIC, 
        DYNAMIC
    };

    class VertexBuffer
    {
    public:
        virtual void resize(uint size) = 0;
        virtual void setLayout(const LayoutBuffer& layout) = 0;
        virtual void setData(uint size, const void* data) = 0;

        virtual void releasePointer() = 0;

        virtual void bind() = 0;
        virtual void unBind() = 0;

        template<typename T>
        T* getPointer()
        {
            return (T*)getPointerInternal();
        }
    protected:
        virtual void* getPointerInternal() = 0;
    public:
        static QSharedPointer<VertexBuffer> create(BufferUsage usage = BufferUsage::DYNAMIC);
    };
}

#endif