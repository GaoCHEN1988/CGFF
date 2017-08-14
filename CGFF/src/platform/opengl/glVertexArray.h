#ifndef CGFF_GL_VERTEX_ARRAY_H
#define CGFF_GL_VERTEX_ARRAY_H

#include "graphic/api/vertexArray.h"
#include <QOpenGLVertexArrayObject>

namespace CGFF {

    class GLVertexArray : public VertexArray
    {
    public:
        GLVertexArray();
        virtual ~GLVertexArray();

        inline QSharedPointer<VertexBuffer> getBuffer(uint index = 0) override { return m_buffers[index]; }
        void pushBuffer(QSharedPointer<VertexBuffer> buffer) override;

        void bind()  override;
        void unBind() override;

        void draw(uint count) const override;

    private:
        QOpenGLVertexArrayObject m_glVertexArray;
        QVector<QSharedPointer<VertexBuffer>> m_buffers;
    };

}

#endif