#ifndef DEBUG_LAYER_H
#define DEBUG_LAYER_H

#include "graphic/layer/layer2D.h"
#include "graphic/sprite.h"
#include "graphic/label.h"

namespace CGFF {

    class DebugLayer : public Layer2D
    {
    public:
        DebugLayer(QSize screenSize);
        virtual ~DebugLayer() {};

        void init() override;
        void render() override;
        void resize(int width, int height) override;

    };

}

#endif
