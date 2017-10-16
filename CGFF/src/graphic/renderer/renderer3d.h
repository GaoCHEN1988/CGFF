#ifndef CGFF_RENDERER_3D_H
#define CGFF_RENDERER_3D_H

#include "graphic/mesh.h"
#include "graphic/renderCommand.h"
#include "graphic/camera/camera.h"
#include "graphic/lightSetup.h"

namespace CGFF {

    typedef QVector<RenderCommand> CommandQueue;
    typedef QVector<RendererUniform> SystemUniformList;

    enum VSSystemUniformIndices : int
    {
        VSSystemUniformIndex_ProjectionMatrix = 0,
        VSSystemUniformIndex_ViewMatrix = 1,
        VSSystemUniformIndex_ModelMatrix = 2,
        VSSystemUniformIndex_CameraPosition = 3,
        VSSystemUniformIndex_Size = 4
    };

    enum PSSystemUniformIndices : int
    {
        PSSystemUniformIndex_Lights = 0,
        PSSystemUniformIndex_Size = 1
    };

     /*Base class for all 3D renderers.
     
     Implementations:
    		- ForwardRenderer.h  (WIP)
    		- DeferredRenderer.h (TBA)*/
    
    class Renderer3D
    {
    public:
		virtual ~Renderer3D() {}
        virtual void init() = 0;
        virtual void begin() = 0;
		virtual void beginScene(QSharedPointer<Camera> camera) = 0;
        // TODO: Submit needs to be replaced by some sort of macro
        virtual void submit(const RenderCommand& command) = 0;
        virtual void submitMesh(const QSharedPointer<Mesh>& mesh, const QMatrix4x4& transform) = 0;
        virtual void submitLightSetup(const QSharedPointer<LightSetup>& lightSetup) = 0;
        virtual void submitLightEntity(const QSharedPointer<Mesh>& lightMesh, const QMatrix4x4& transform, const QVector4D& color = QVector4D()) {};
		virtual void endScene() = 0;
        virtual void end() = 0;
        virtual void flush() = 0;
		virtual void close() {};
		virtual void setScreenBufferSize(int width, int height) 
        { 
            m_screenBufferWidth = width; 
            m_screenBufferHeight = height; 
            m_screenSize = QSize(width, height);
        }

    protected:
        CommandQueue m_commandQueue;
        CommandQueue m_lightCommandQueue;
        SystemUniformList m_systemUniforms;
		int m_screenBufferWidth; 
		int m_screenBufferHeight;
        QSize m_screenSize;
    };
}

#endif