#ifndef CGFF_DEFERRED_RENDERER_H
#define CGFF_DEFERRED_RENDERER_H

#include "renderer3d.h"
#include "graphic/api/gBuffer.h"

namespace CGFF {

    class DeferredRenderer : public Renderer3D
    {
    public:
        DeferredRenderer(const QSize& size);
        DeferredRenderer(int width, int height);
        virtual ~DeferredRenderer() {}

        void init() override;
        void begin() override;
        void beginScene(QSharedPointer<Camera> camera) override;
        void submit(const RenderCommand& command) override;
        void submitMesh(const QSharedPointer<Mesh>&, const QMatrix4x4& transform) override;
        void submitLightSetup(const QSharedPointer<LightSetup>& lightSetup) override;
        void submitLightEntity(const QSharedPointer<Mesh>& lightMesh, const QMatrix4x4& transform, const QVector4D& color = QVector4D()) override;
        void endScene() override;
        void end() override;
        void flush() override;
        void close() override;

    private:
        void setSystemUniforms(QSharedPointer<Shader> shader);

        void renderToGBuffer();

    private:
        QSharedPointer<uchar> m_VSSystemUniformBuffer;
        uint m_VSSystemUniformBufferSize;
        QSharedPointer<uchar> m_PSSystemUniformBuffer;
        uint m_PSSystemUniformBufferSize;

        QVector<uint> m_VSSystemUniformBufferOffsets;
        QVector<uint> m_PSSystemUniformBufferOffsets;

        QSharedPointer<GBuffer> m_GBuffer;
        uint m_width, m_height;
        QSharedPointer<Shader> m_geometryPassShader;
        QSharedPointer<Shader> m_lightPassShader;
        QSharedPointer<MaterialInstance> m_geometryPassMaterial;
        QSharedPointer<MaterialInstance> m_lightPassPassMaterial;
        QSharedPointer<Mesh> m_screenQuad;
    };

}

#endif