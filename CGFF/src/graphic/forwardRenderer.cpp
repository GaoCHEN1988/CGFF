#include "forwardRenderer.h"

namespace CGFF {
    ForwardRenderer::ForwardRenderer()
    {}
    void ForwardRenderer::init()
    {
    }
    void ForwardRenderer::begin() 
    {
        m_commandQueue.clear();
    }

    void ForwardRenderer::submit(const RenderCommand& command)
    {
        m_commandQueue.push_back(command);
    }

    void ForwardRenderer::submitMesh(QSharedPointer<Camera> camera, QSharedPointer<Mesh> mesh, const QMatrix4x4& transform)
    {
        //QMatrix4x4 proj_matrix = camera->getProjectionMatrix();
        RendererUniform proj_matrix;
        proj_matrix.type = UniformType::QMatrix4x4;
        proj_matrix.data = (void*)&camera->getProjectionMatrix();
        proj_matrix.uniform = SHADER_UNIFORM_PROJECTION_MATRIX_NAME;
       
        RendererUniform vw_matrix;
        vw_matrix.type = UniformType::QMatrix4x4;
        vw_matrix.data = (void*)&camera->getViewMatrix();
        vw_matrix.uniform = SHADER_UNIFORM_VIEW_MATRIX_NAME;

        RendererUniform ml_matrix;
        ml_matrix.type = UniformType::QMatrix4x4;
        ml_matrix.data = (void*)&transform;
        ml_matrix.uniform = SHADER_UNIFORM_MODEL_MATRIX_NAME;

        RenderCommand command;
        command.mesh = mesh;
        command.uniforms.push_back(proj_matrix);
        command.uniforms.push_back(vw_matrix);
        command.uniforms.push_back(ml_matrix);
        m_commandQueue.push_back(command);
    }

    void ForwardRenderer::end() 
    {
        // TODO: Batching and sorting
    }
    void ForwardRenderer::flush() 
    {
        // TODO: Shader binding, texture sorting, visibility testing, etc.

        GL->glEnable(GL_DEPTH_TEST);
        GL->glDepthFunc(GL_LEQUAL);

        for (uint i = 0; i < m_commandQueue.size(); i++)
        {
            const RenderCommand& command = m_commandQueue[i];
            command.mesh->getMaterialInstance()->getMaterial()->getShader()->bind();
            setRequiredUniforms(command.mesh->getMaterialInstance()->getMaterial()->getShader(), command.uniforms);
            for (uint i = 0; i < command.uniforms.size(); i++)
                command.mesh->getMaterialInstance()->setRendererUniform(command.uniforms[i]);

            command.mesh->render(*this);
        }
    }

    void ForwardRenderer::setRequiredUniforms(QSharedPointer<QOpenGLShaderProgram> shader, const QVector<RendererUniform>& uniforms)
    {

        for (uint i = 0; i < uniforms.size(); i++)
            SetRendererUniform(uniforms[i], shader);
    }
}