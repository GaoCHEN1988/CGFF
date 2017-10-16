#ifndef CGFF_FRAMEBUFFER_DEPTH_CUBE_H
#define CGFF_FRAMEBUFFER_DEPTH_CUBE_H

#include "framebuffer.h"

namespace CGFF {

    class FramebufferDepthCube : public Framebuffer
    {
    public:
        static QSharedPointer<FramebufferDepthCube> create(int size);
    };
}

#endif