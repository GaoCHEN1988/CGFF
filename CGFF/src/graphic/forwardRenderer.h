#ifndef FORWARD_RENDERER_H
#define FORWARD_RENDERER_H

#include "renderer3d.h"

namespace CGFF {

    class ForwardRenderer : public Renderer3D
    {
    private:

    public:
        ForwardRenderer();
        void init() override;
        void begin() override;
        void submit(QSharedPointer<Mesh>& mesh) override;
        void end() override;
        void flush() override;
    };
}

#endif
