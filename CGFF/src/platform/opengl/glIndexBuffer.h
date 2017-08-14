#ifndef CGFF_GL_INDEX_BUFFER_H
#define CGFF_GL_INDEX_BUFFER_H

#include "graphic/api/indexBuffer.h"
#include <QOpenGLBuffer>

namespace CGFF {

    class GLIndexBuffer : public IndexBuffer
    {
    public:
        GLIndexBuffer(uint* data, uint count);
        virtual ~GLIndexBuffer();

        void bind() override;
        void unBind() override;

        uint getCount() const override;

    private:
        QOpenGLBuffer m_glIndexBuffer;
        uint m_count;
    };

}

#endif