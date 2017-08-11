#ifndef CGFF_RENDERER_3D_H
#define CGFF_RENDERER_3D_H

#include "mesh.h"
#include "renderCommand.h"
#include "camera/camera.h"
#include "lightSetup.h"

namespace CGFF {

    typedef QVector<RenderCommand> CommandQueue;
    typedef QVector<RendererUniform> SystemUniformList;

     /*Base class for all 3D renderers.
     
     Implementations:
    		- ForwardRenderer.h  (WIP)
    		- DeferredRenderer.h (TBA)*/
    
    class Renderer3D
    {
    public:
        virtual void init() = 0;
        virtual void begin() = 0;
        //virtual void submit(QSharedPointer<Mesh>&) = 0;
        // TODO: Submit needs to be replaced by some sort of macro
        virtual void submit(const RenderCommand& command) = 0;
        virtual void submitMesh(QSharedPointer<Camera> camera, QSharedPointer<Mesh> mesh, const QMatrix4x4& transform) = 0;
        virtual void submitLightSetup(const QSharedPointer<LightSetup>& lightSetup) = 0;
        virtual void end() = 0;
        virtual void flush() = 0;

    protected:
        CommandQueue m_commandQueue;
        SystemUniformList m_systemUniforms;
    };
}

#endif