#ifndef CGFF_VERTEX_ARRAY_H
#define CGFF_VERTEX_ARRAY_H

#include "vertexBuffer.h"

namespace CGFF {

    class VertexArray
    {
    public:
        virtual QSharedPointer<VertexBuffer> getBuffer(uint index = 0) = 0;
        virtual void pushBuffer(QSharedPointer<VertexBuffer> buffer) = 0;

        virtual void bind() = 0;
        virtual void unBind() = 0;

        virtual void draw(uint count) const = 0;

    public:
        static QSharedPointer<VertexArray> create();

    private:
        QVector<VertexBuffer*> m_buffers;
    };

}

#endif