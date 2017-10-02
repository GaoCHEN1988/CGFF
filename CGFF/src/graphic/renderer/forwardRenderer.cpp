#include "forwardRenderer.h"
#include "renderer.h"
#include "graphic/meshFactory.h"

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

    QSharedPointer<Shader>  debugDepthQuadShader;
    float near_plane = 1.0f, far_plane = 7.5f;

    ForwardRenderer::ForwardRenderer(const QSize& size)
        : m_VSSystemUniformBuffer(nullptr)
        , m_VSSystemUniformBufferSize(0)
        , m_PSSystemUniformBuffer(nullptr)
        , m_PSSystemUniformBufferSize(0)
        , m_VSSystemUniformBufferOffsets()
        , m_PSSystemUniformBufferOffsets()
        , m_depthBuffer(nullptr)
    {
		setScreenBufferSize(size.width(), size.height());
		init();
	}

	ForwardRenderer::ForwardRenderer(int width, int height)
        : m_VSSystemUniformBuffer(nullptr)
        , m_VSSystemUniformBufferSize(0)
        , m_PSSystemUniformBuffer(nullptr)
        , m_PSSystemUniformBufferSize(0)
        , m_VSSystemUniformBufferOffsets()
        , m_PSSystemUniformBufferOffsets()
        , m_depthBuffer(nullptr)
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

#ifdef TEST_DEPTH_MAP

        debugDepthQuadShader = Shader::createFromFile("DebugDepthShader ",
            "/shaders/advanced_lighting/3.1.2.debug_quad.vs",
            "/shaders/advanced_lighting/3.1.2.debug_quad_depth.fs");

        m_depthBuffer = FramebufferDepth::create(m_screenBufferWidth, m_screenBufferHeight);

        m_screenMaterial = QSharedPointer<Material>(new Material(debugDepthQuadShader));

        m_screenQuad = MeshFactory::CreateQuad(-1, -1, m_screenBufferWidth, m_screenBufferHeight,
            QSharedPointer<MaterialInstance>(new MaterialInstance(m_screenMaterial)));

        

#endif

	}
    void ForwardRenderer::begin() 
    {
		Renderer::setViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);

        m_commandQueue.clear();
        m_systemUniforms.clear();

#ifdef TEST_DEPTH_MAP

        if (m_screenSize != m_depthBuffer->getSize())
        {
            m_depthBuffer.clear();
            m_depthBuffer = FramebufferDepth::create(m_screenBufferWidth, m_screenBufferHeight);
        }

        m_depthBuffer->bind();

        Renderer::setDepthTesting(true);
#endif
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
        RenderCommand command;
        command.mesh = mesh;
		command.transform = transform;
		command.shader = mesh->getMaterialInstance()->getMaterial()->getShader();
        m_commandQueue.push_back(command);
    }

    void ForwardRenderer::submitLightSetup(const QSharedPointer<LightSetup>& lightSetup)
    {
        auto lights = lightSetup->getLights();
        Q_ASSERT(lights.size() <= 1);//To do: support multiple lights
        for (int i = 0; i < lights.size(); i++)
        {
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
#ifdef TEST_DEPTH_MAP
        //m_depthBuffer->bind();
        //m_depthBuffer->clear();
#endif
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
#ifdef TEST_DEPTH_MAP
        m_depthBuffer->unBind();

        m_depthBuffer->getTexture()->bind();
        m_screenMaterial->setUniform("near_plane", near_plane);
        m_screenMaterial->setUniform("far_plane", far_plane);
        m_screenMaterial->setTexture("depthMap", m_depthBuffer->getTexture());

        m_screenMaterial->bind();
        m_screenQuad->bind();

        m_screenQuad->draw();
        m_screenQuad->unBind();
        m_screenMaterial->unbind();
#endif
    }

	void ForwardRenderer::close()
	{
		m_commandQueue.clear();
	}

	void ForwardRenderer::setSystemUniforms(QSharedPointer<Shader> shader)
	{
		// TODO: Set per-mesh buffer to slot 1
		shader->setVSSystemUniformBuffer(m_VSSystemUniformBuffer.data(), m_VSSystemUniformBufferSize, 0);
		shader->setPSSystemUniformBuffer(m_PSSystemUniformBuffer.data(), m_PSSystemUniformBufferSize, 0);
	}
}