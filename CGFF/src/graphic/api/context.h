#ifndef CGFF_CONTEXT_H
#define CGFF_CONTEXT_H

#include "utils/qtopengl.h"
#include <QWindow>

namespace CGFF {

    enum class RenderAPI
    {
        NONE, 
		OPENGL, 
		DIRECT3D
    };

    class Context
    {
    public:
        static void create(QWindow *parent = Q_NULLPTR);

        static RenderAPI getRenderAPI() { return s_renderAPI; }
        static void setRenderAPI(RenderAPI api) { s_renderAPI = api; }

    protected:
        static QSharedPointer<Context> s_context;
        static RenderAPI s_renderAPI;
    };
}

#endif