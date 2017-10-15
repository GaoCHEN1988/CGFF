#ifndef CGFF_FORWARD_RENDERER_H
#define CGFF_FORWARD_RENDERER_H

#include "renderer3d.h"

#include "graphic/api/framebufferDepth.h"
#include "graphic/api/framebufferDepthCube.h"
#include "graphic/api/framebuffer2D.h"

//#define TEST_DEPTH_MAP
//#define TEST_DEPTH_MAP_CUBE
#define TEST_FRAME_BUFFER

namespace CGFF {

    class ForwardRenderer : public Renderer3D
    {
    public:
        ForwardRenderer(const QSize& size);
		ForwardRenderer(int width, int height);
		virtual ~ForwardRenderer() {}

        void init() override;
        void begin() override;
		void beginScene(QSharedPointer<Camera> camera) override;
        void submit(const RenderCommand& command) override;
        void submitMesh(const QSharedPointer<Mesh>& mesh, const QMatrix4x4& transform) override;
        void submitLightSetup(const QSharedPointer<LightSetup>& lightSetup) override;
		void endScene() override;
		void end() override;
        void flush() override;
		void close() override;

    private:
        //void setRequiredUniforms(QSharedPointer<QOpenGLShaderProgram> shader, const QVector<RendererUniform>& uniforms);
        //void setSystemUniforms(QSharedPointer<QOpenGLShaderProgram> shader);
		void setSystemUniforms(QSharedPointer<Shader> shader);
	
        void renderToFrameBuffer();
        void renderToDepthMap();
        void renderToDepthMapCube();
	private:
		QSharedPointer<uchar> m_VSSystemUniformBuffer;
		uint m_VSSystemUniformBufferSize;
		QSharedPointer<uchar> m_PSSystemUniformBuffer;
		uint m_PSSystemUniformBufferSize;

		QVector<uint> m_VSSystemUniformBufferOffsets;
		QVector<uint> m_PSSystemUniformBufferOffsets;

        QSharedPointer<FramebufferDepth> m_depthBuffer;
        QSharedPointer<MaterialInstance> m_depthMappingMaterial;

        QSharedPointer<FramebufferDepthCube> m_depthCubeBuffer;
        QSharedPointer<MaterialInstance> m_depthMappingCubeMaterial;

        QSharedPointer<Framebuffer2D> m_frameBuffer;

        QSharedPointer<Mesh> m_screenQuad;
        QSharedPointer<MaterialInstance> m_screenQuadMaterial;

    };
}

#endif
