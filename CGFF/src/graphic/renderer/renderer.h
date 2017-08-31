#ifndef CGFF_RENDERER_H
#define CGFF_RENDERER_H

#include "utils/qtopengl.h"
#include "common.h"

namespace CGFF {

    enum RendererBufferType
    {
        RENDERER_BUFFER_NONE = BIT(0),
        RENDERER_BUFFER_COLOR = BIT(1),
        RENDERER_BUFFER_DEPTH = BIT(2),
        RENDERER_BUFFER_STENCIL = BIT(3)
    };

    enum class RendererBlendFunction
    {
        NONE,
        ZERO,
        ONE,
        SOURCE_ALPHA,
        DESTINATION_ALPHA,
        ONE_MINUS_SOURCE_ALPHA
    };

    enum class RendererBlendEquation
    {
        NONE,
        ADD,
        SUBTRACT
    };

    class Renderer
    {
    protected:
        virtual void initInternal() = 0;

        virtual void clearInternal(uint buffer) = 0;
        virtual void presentInternal() = 0;

        virtual void setDepthTestingInternal(bool enabled) = 0;
        virtual void setBlendInternal(bool enabled) = 0;
        virtual void setViewportInternal(uint x, uint y, uint width, uint height) = 0;

        virtual void setBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination) = 0;
        virtual void setBlendEquationInternal(RendererBlendFunction blendEquation) = 0;

        virtual QString getTitleInternal() = 0;
    public:
        inline static void clear(uint buffer) { s_instance->clearInternal(buffer); }
        inline static void present() { s_instance->presentInternal(); }

        inline static void setDepthTesting(bool enabled) { s_instance->setDepthTestingInternal(enabled); }
        inline static void setBlend(bool enabled) { s_instance->setBlendInternal(enabled); }
        inline static void setViewport(uint x, uint y, uint width, uint height) { s_instance->setViewportInternal(x, y, width, height); }

        inline static void setBlendFunction(RendererBlendFunction source, RendererBlendFunction destination) { s_instance->setBlendFunctionInternal(source, destination); }
        inline static void setBlendEquation(RendererBlendFunction blendEquation) { s_instance->setBlendEquationInternal(blendEquation); }

        inline static QString getTitle() { return s_instance->getTitleInternal(); }
    public:
        static void init();
        inline static QSharedPointer<Renderer> getRenderer() { return s_instance; }

    private:
        static QSharedPointer<Renderer> s_instance;
    };

}

#endif