#ifndef RENDERER_3D_H
#define RENDERER_3D_H

#include "../utils/qtopengl.h"
#include "../maths/qtmaths.h"
#include "mesh.h"

namespace CGFF {

    
     /*Base class for all 3D renderers.
     
     Implementations:
    		- ForwardRenderer.h  (WIP)
    		- DeferredRenderer.h (TBA)*/
    
    class Renderer3D
    {
    protected:
        QVector<QSharedPointer<Mesh>> m_drawQueue;
    public:
        virtual void init() = 0;
        virtual void begin() = 0;
        virtual void submit(QSharedPointer<Mesh>&) = 0;
        virtual void end() = 0;
        virtual void flush() = 0;

    };
}

#endif