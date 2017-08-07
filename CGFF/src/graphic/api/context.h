#ifndef CGFF_CONTEXT_H
#define CGFF_CONTEXT_H

namespace CGFF {

    enum class RenderAPI
    {
        NONE, OPENGL, DIRECT3D
    };

    class Context
    {
    public:
        static void Create(void* deviceContext) {};

        static RenderAPI getRenderAPI() { return s_renderAPI; }
        static void setRenderAPI(RenderAPI api) { s_renderAPI = api; }

    protected:
        static Context* s_context;
        static RenderAPI s_renderAPI;
    };
}

#endif