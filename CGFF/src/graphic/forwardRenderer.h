#ifndef FORWARD_RENDERER_H
#define FORWARD_RENDERER_H

#include "renderer3d.h"

namespace CGFF {

    class ForwardRenderer : public Renderer3D
    {
    public:
        ForwardRenderer();
        void init() override;
        void begin() override;
        //void submit(QSharedPointer<Mesh>& mesh) override;
        void submit(const RenderCommand& command) override;
        void submitMesh(QSharedPointer<Camera> camera, QSharedPointer<Mesh> mesh, const QMatrix4x4& transform) override;
        void end() override;
        void flush() override;

    private:
        void setRequiredUniforms(QSharedPointer<QOpenGLShaderProgram> shader, const QVector<RendererUniform>& uniforms);
    };
}

#endif
