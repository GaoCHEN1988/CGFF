#ifndef CGFF_INDEX_BUFFER_H
#define CGFF_INDEX_BUFFER_H

#include "utils/types.h"

namespace CGFF {

    class IndexBuffer
    {
    public:
        virtual void bind() = 0;
        virtual void unBind() = 0;

        virtual uint getCount() const = 0;

    public:     
        static QSharedPointer<IndexBuffer> create(uint* data, uint count);
    };
}

#endif
