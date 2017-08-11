#ifndef CGFF_IRENDERABLE_H
#define CGFF_IRENDERABLE_H

namespace CGFF {

    class Renderer3D;

    class IRenderable
    {
    public:
        virtual void render(Renderer3D& renderer) = 0;
    };
}

#endif