#include "forwardRenderer.h"
#include "renderer.h"
#include "graphic/meshFactory.h"
#include "examples/learnOpengl/learnGLMeshFactory.h"

namespace CGFF {

    //Using for LearnOpenGL tutorial, should not be here
    static QSharedPointer<Shader>  depthMappingShader;
    static QSharedPointer<Shader>  depthMappingCubeShader;
    static float near_plane = -1.0f;
    static float far_plane = 200.0f;
    static const int SHADOW_WIDTH = 2048;
    static const int SHADOW_HEIGHT = 2048;
    static QVector3D g_LightPos(50.0, 50.0, 50.0);
    static QMatrix4x4 lightSpaceMatrix;
    static QSharedPointer<Shader>  hdrShader;
    static float exposure = 0.1f;

    ForwardRenderer::ForwardRenderer(const QSize& size)
        : m_VSSystemUniformBuffer(nullptr)
        , m_VSSystemUniformBufferSize(0)
        , m_PSSystemUniformBuffer(nullptr)
        , m_PSSystemUniformBufferSize(0)
        , m_VSSystemUniformBufferOffsets()
        , m_PSSystemUniformBufferOffsets()
        , m_depthBuffer(nullptr)
        , m_frameBuffer(nullptr)
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
        , m_frameBuffer(nullptr)
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

        depthMappingShader = Shader::createFromFile("DebugDepthShader",
            "/shaders/advanced_lighting/3.1.3.shadow_mapping_depth.vs",
            "/shaders/advanced_lighting/3.1.3.shadow_mapping_depth.fs");

        m_depthBuffer = FramebufferDepth::create(SHADOW_WIDTH, SHADOW_HEIGHT);

        m_depthMappingMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(depthMappingShader))));

#endif

#ifdef TEST_DEPTH_MAP_CUBE

        depthMappingCubeShader = Shader::createFromFile("DebugDepthCubeShader",
            "/shaders/advanced_lighting/3.2.1.point_shadows_depth.vs",
            "/shaders/advanced_lighting/3.2.1.point_shadows_depth.fs", 
            "/shaders/advanced_lighting/3.2.1.point_shadows_depth.gs");

        m_depthCubeBuffer = FramebufferDepthCube::create(SHADOW_WIDTH);

        m_depthMappingCubeMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(depthMappingCubeShader))));

#endif

#ifdef TEST_FRAME_BUFFER

        m_frameBuffer = Framebuffer2D::create(m_screenBufferWidth, m_screenBufferHeight);

        hdrShader = Shader::createFromFile("HdrShader ",
            "/shaders/advanced_lighting/6.hdr.vs",
            "/shaders/advanced_lighting/6.hdr.fs");

        m_screenQuadMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(hdrShader))));

        //QMatrix4x4 proj = QMatrix4x4();
        //proj.ortho(0, (float)m_screenSize.width(), (float)m_screenSize.height(), 0, -1.0f, 100.0f);
        //m_screenQuadMaterial->setUniform("projectionMatrix", proj);

        m_screenQuad = LearnGL::CreateScreenQuad(m_screenQuadMaterial);

        m_screenQuadMaterial->setTexture("hdrBuffer", m_frameBuffer->getTexture());
#endif
	}
    void ForwardRenderer::begin() 
    {
		Renderer::setViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);
        m_commandQueue.clear();
        m_systemUniforms.clear();
#ifdef TEST_FRAME_BUFFER
        if (m_screenSize != m_frameBuffer->getSize())
        {
            m_frameBuffer.clear();
            m_frameBuffer = Framebuffer2D::create(m_screenSize.width(), m_screenSize.height());
        }

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

    void ForwardRenderer::submitMesh(const QSharedPointer<Mesh>& mesh, const QMatrix4x4& transform)
    {
        RenderCommand command;
        command.mesh = mesh;
		command.transform = transform;
		command.shader = mesh->getMaterialInstance()->getMaterial()->getShader();
        m_commandQueue.push_back(command);
    }

    void ForwardRenderer::submitLightSetup(const QSharedPointer<LightSetup>& lightSetup)
    {
        //To do
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
        
        renderToDepthMap();
        m_depthBuffer->getTexture()->bind();
#endif

#ifdef TEST_DEPTH_MAP_CUBE

        renderToDepthMapCube();
        m_depthCubeBuffer->getTexture()->bind();

#endif

#ifdef TEST_FRAME_BUFFER
        if (Renderer::getRenderTarget() == Render3DTarget::BUFFER)
        {
            m_frameBuffer->bind();
            m_frameBuffer->clear();
            m_screenQuadMaterial->setTexture("hdrBuffer", m_frameBuffer->getTexture());
            Renderer::setViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);
        }
#endif
		for (uint i = 0; i < m_commandQueue.size(); i++)
		{
			const RenderCommand& command = m_commandQueue[i];
			QSharedPointer<MaterialInstance> material = command.mesh->getMaterialInstance();
			int materialRenderFlags = material->getRenderFlags();
#ifdef TEST_DEPTH_MAP
            material->setTexture("shadowMap", m_depthBuffer->getTexture());
            material->setUniform("lightSpaceMatrix", lightSpaceMatrix);
            material->setUniform("lightPos", g_LightPos);
#endif
#ifdef TEST_DEPTH_MAP_CUBE
            material->setTexture("depthMap", m_depthCubeBuffer->getTexture());
            material->setUniform("far_plane", far_plane);
            material->setUniform("lightPos", g_LightPos);

            if (i == m_commandQueue.size() - 1)
            {
                material->setUniform("reverse_normals", 1);
            }
            else
            {
                material->setUniform("reverse_normals", 0);
            }
#endif
            Renderer::setDepthTesting((materialRenderFlags & (int)Material::RenderFlags::DISABLE_DEPTH_TEST) == 0);
			memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(QMatrix4x4));
			setSystemUniforms(command.shader);
			command.mesh->render(*this);
		}

#ifdef TEST_FRAME_BUFFER
        if (Renderer::getRenderTarget() == Render3DTarget::BUFFER)
        {      

            m_frameBuffer->unBind();
            m_frameBuffer->clear();
            m_screenQuadMaterial->setUniform("hdr", true);
            m_screenQuadMaterial->setUniform("exposure", exposure);
            m_screenQuad->render(*this);

        }

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

    void ForwardRenderer::renderToFrameBuffer()
    {

    }

    void ForwardRenderer::renderToDepthMap()
    {
        m_depthBuffer->bind();
        m_depthBuffer->clear();
        Renderer::setViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

        QMatrix4x4 light_projection;
        light_projection.ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);
        QMatrix4x4 light_view;
        light_view.lookAt(g_LightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
        lightSpaceMatrix = light_projection * light_view;
        m_depthMappingMaterial->setUniform("lightSpaceMatrix", lightSpaceMatrix);

        for (uint i = 0; i < m_commandQueue.size(); i++)
        {
            RenderCommand command;
            command.mesh = QSharedPointer<Mesh>(new Mesh(m_commandQueue[i].mesh));
            command.mesh->setMaterial(m_depthMappingMaterial);
            command.transform = m_commandQueue[i].transform;
            command.shader = m_depthMappingMaterial->getMaterial()->getShader();

            Renderer::setDepthTesting(true);
            memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(QMatrix4x4));
            setSystemUniforms(command.shader);
            command.mesh->render(*this);
        }

        m_depthBuffer->unBind();

        Renderer::setViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);
    }

    void ForwardRenderer::renderToDepthMapCube()
    {
        QMatrix4x4 shadowProj;
        shadowProj.perspective(90.0f, static_cast<float>(SHADOW_WIDTH) / static_cast<float>(SHADOW_WIDTH), near_plane, far_plane);
        QVector<QMatrix4x4> shadowTransforms;

        QMatrix4x4 light_view;
        light_view.lookAt(g_LightPos, g_LightPos + QVector3D(1.0f, 0.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f));
        shadowTransforms.push_back(shadowProj * light_view);

        light_view.setToIdentity();
        light_view.lookAt(g_LightPos, g_LightPos + QVector3D(-1.0f, 0.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f));
        shadowTransforms.push_back(shadowProj * light_view);

        light_view.setToIdentity();
        light_view.lookAt(g_LightPos, g_LightPos + QVector3D(0.0f, 1.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f));
        shadowTransforms.push_back(shadowProj * light_view);

        light_view.setToIdentity();
        light_view.lookAt(g_LightPos, g_LightPos + QVector3D(0.0f, -1.0f, 0.0f), QVector3D(0.0f, 0.0f, -1.0f));
        shadowTransforms.push_back(shadowProj * light_view);

        light_view.setToIdentity();
        light_view.lookAt(g_LightPos, g_LightPos + QVector3D(0.0f, 0.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f));
        shadowTransforms.push_back(shadowProj * light_view);

        light_view.setToIdentity();
        light_view.lookAt(g_LightPos, g_LightPos+QVector3D(0.0f, 0.0f, -1.0f), QVector3D(0.0f, -1.0f, 0.0f));
        shadowTransforms.push_back(shadowProj * light_view);

        m_depthCubeBuffer->bind();
        m_depthCubeBuffer->clear();
        Renderer::setViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

        m_depthMappingCubeMaterial->setUniform("shadowMatrices", shadowTransforms);
        m_depthMappingCubeMaterial->setUniform("far_plane", far_plane);
        m_depthMappingCubeMaterial->setUniform("lightPos", g_LightPos);

        for (uint i = 0; i < m_commandQueue.size(); i++)
        {
            RenderCommand command;
            command.mesh = QSharedPointer<Mesh>(new Mesh(m_commandQueue[i].mesh));
            command.mesh->setMaterial(m_depthMappingCubeMaterial);
            command.transform = m_commandQueue[i].transform;
            command.shader = m_depthMappingCubeMaterial->getMaterial()->getShader();

            Renderer::setDepthTesting(true);
            memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(QMatrix4x4));
            setSystemUniforms(command.shader);
            command.mesh->render(*this);
        }

        m_depthCubeBuffer->unBind();

        Renderer::setViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);
    }
}