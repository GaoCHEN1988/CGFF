#include "forwardRenderer.h"
#include "renderer.h"

namespace CGFF {

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

    ForwardRenderer::ForwardRenderer()
    {
		setScreenBufferSize(openglWidgetSize.width(), openglWidgetSize.height());
		init();
	}

	ForwardRenderer::ForwardRenderer(int width, int height)
	{
		setScreenBufferSize(width, height);
		init();
	}

    void ForwardRenderer::init()
    {
		m_commandQueue.reserve(1000);

		//
		// Vertex shader system uniforms
		//
		m_VSSystemUniformBufferSize = sizeof(QMatrix4x4) + sizeof(QMatrix4x4) + sizeof(QVector3D) + sizeof(QMatrix4x4);
		m_VSSystemUniformBuffer = QSharedPointer<uchar>( new uchar[m_VSSystemUniformBufferSize]);
		memset(m_VSSystemUniformBuffer.data(), 0, m_VSSystemUniformBufferSize);
		m_VSSystemUniformBufferOffsets.resize(VSSystemUniformIndex_Size);

		// Per Scene System Uniforms
		m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ProjectionMatrix] = 0;
		m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ViewMatrix] = m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ProjectionMatrix] + sizeof(QMatrix4x4);
		m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix] = m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ViewMatrix] + sizeof(QMatrix4x4);
   
		// Per Mesh System Uniforms
		// Note: Model Matrix should be here instead of camera position; this will get sorted when it gets moved to a separate buffer
		m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_CameraPosition] = m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix] + sizeof(QMatrix4x4);

		//
		// Pixel/fragment shader system uniforms
		//
		m_PSSystemUniformBufferSize = sizeof(Light);
		m_PSSystemUniformBuffer = QSharedPointer<uchar>(new uchar[m_PSSystemUniformBufferSize]);
		memset(m_PSSystemUniformBuffer.data(), 0, m_PSSystemUniformBufferSize);
		m_PSSystemUniformBufferOffsets.resize(PSSystemUniformIndex_Size);

		// Per Scene System Uniforms
		m_PSSystemUniformBufferOffsets[PSSystemUniformIndex_Lights] = 0;

	}
    void ForwardRenderer::begin() 
    {
        m_commandQueue.clear();
        m_systemUniforms.clear();
    }

	void ForwardRenderer::beginScene(QSharedPointer<Camera> camera)
	{
		memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ProjectionMatrix], &camera->getProjectionMatrix(), sizeof(QMatrix4x4));
		memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ViewMatrix], &camera->getViewMatrix(), sizeof(QMatrix4x4));
		memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_CameraPosition], &camera->getPosition(), sizeof(QVector3D));
	}

    void ForwardRenderer::submit(const RenderCommand& command)
    {
        m_commandQueue.push_back(command);
    }

    void ForwardRenderer::submitMesh(QSharedPointer<Mesh> mesh, const QMatrix4x4& transform)
    {
        ////QMatrix4x4 proj_matrix = camera->getProjectionMatrix();
        //RendererUniform proj_matrix;
        //proj_matrix.type = UniformType::QMatrix4x4;
        //proj_matrix.data = (void*)&camera->getProjectionMatrix();
        //proj_matrix.uniform = SHADER_UNIFORM_PROJECTION_MATRIX_NAME;
       
        //RendererUniform vw_matrix;
        //vw_matrix.type = UniformType::QMatrix4x4;
        //vw_matrix.data = (void*)&camera->getViewMatrix();
        //vw_matrix.uniform = SHADER_UNIFORM_VIEW_MATRIX_NAME;

        //RendererUniform ml_matrix;
        //ml_matrix.type = UniformType::QMatrix4x4;
        //ml_matrix.data = (void*)&transform;
        //ml_matrix.uniform = SHADER_UNIFORM_MODEL_MATRIX_NAME;

        RenderCommand command;
        command.mesh = mesh;
		command.transform = transform;
		command.shader = mesh->getMaterialInstance()->getMaterial()->getShader();
 /*       command.uniforms.push_back(proj_matrix);
        command.uniforms.push_back(vw_matrix);
        command.uniforms.push_back(ml_matrix);

        for (int i = 0; i < m_systemUniforms.size(); i++)
            command.uniforms.push_back(m_systemUniforms[i]);*/

        m_commandQueue.push_back(command);
    }

    void ForwardRenderer::submitLightSetup(const QSharedPointer<LightSetup>& lightSetup)
    {
        auto lights = lightSetup->getLights();
        Q_ASSERT(lights.size() <= 1, "Only one light is supported at the moment!");
        for (int i = 0; i < lights.size(); i++)
        {
            //QSharedPointer<Light> light = lights[i];
            //RendererUniform u_LightPosition;
            //u_LightPosition.type = UniformType::QVector3D;
            //u_LightPosition.data = (void*)&light->position;
            //u_LightPosition.uniform = SHADER_UNIFORM_LIGHT_POSITION;
            //m_systemUniforms.push_back({ SHADER_UNIFORM_LIGHT_POSITION,  (void*)&light->position, UniformType::QVector3D });
            //m_systemUniforms.push_back({ SHADER_UNIFORM_LIGHT_ATTENUATION,  (void*)&light->attenuation, UniformType::GLfloat });
            ////m_systemUniforms.push_back({ SHADER_UNIFORM_LIGHT_COLOR,  (void*)&light->color, UniformType::QVector4D });

			memcpy(m_PSSystemUniformBuffer.data() + m_PSSystemUniformBufferOffsets[PSSystemUniformIndex_Lights], lights[i].data(), sizeof(Light));

        }
    }

	void ForwardRenderer::endScene()
	{

	}

    void ForwardRenderer::end() 
    {
        // TODO: Batching and sorting
    }
    void ForwardRenderer::flush() 
    {
        // TODO: Shader binding, texture sorting, visibility testing, etc.

        //GL->glEnable(GL_DEPTH_TEST);
        //GL->glDepthFunc(GL_LEQUAL);
        //for (uint i = 0; i < m_commandQueue.size(); i++)
        //{
        //    const RenderCommand& command = m_commandQueue[i];
        //    command.mesh->getMaterialInstance()->getMaterial()->getShader()->bind();
        //    setRequiredUniforms(command.mesh->getMaterialInstance()->getMaterial()->getShader(), command.uniforms);
        //    for (uint i = 0; i < command.uniforms.size(); i++)
        //        command.mesh->getMaterialInstance()->setRendererUniform(command.uniforms[i]);
        //    command.mesh->render(*this);
        //}

		for (uint i = 0; i < m_commandQueue.size(); i++)
		{
			const RenderCommand& command = m_commandQueue[i];
			QSharedPointer<MaterialInstance> material = command.mesh->getMaterialInstance();
			int materialRenderFlags = material->getRenderFlags();

			Renderer::setDepthTesting((materialRenderFlags & (int)Material::RenderFlags::DISABLE_DEPTH_TEST) == 0);
			memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(QMatrix4x4));
			setSystemUniforms(command.shader);
			command.mesh->render(*this);
		}

    }

    //void ForwardRenderer::setRequiredUniforms(QSharedPointer<QOpenGLShaderProgram> shader, const QVector<RendererUniform>& uniforms)
    //{
    //    for (uint i = 0; i < uniforms.size(); i++)
    //        SetRendererUniform(uniforms[i], shader);
    //}

    //void ForwardRenderer::setSystemUniforms(QSharedPointer<QOpenGLShaderProgram> shader)
    //{
    //    for (uint i = 0; i < m_systemUniforms.size(); i++)
    //        SetRendererUniform(m_systemUniforms[i], shader);
    //}

	void ForwardRenderer::setSystemUniforms(QSharedPointer<Shader> shader)
	{
		// TODO: Set per-mesh buffer to slot 1
		shader->setVSSystemUniformBuffer(m_VSSystemUniformBuffer.data(), m_VSSystemUniformBufferSize, 0);
		shader->setPSSystemUniformBuffer(m_PSSystemUniformBuffer.data(), m_PSSystemUniformBufferSize, 0);
	}
}