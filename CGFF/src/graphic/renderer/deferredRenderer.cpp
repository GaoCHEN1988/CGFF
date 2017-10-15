#include "deferredRenderer.h"
#include "renderer.h"
#include "graphic/meshFactory.h"

namespace CGFF {

    const QString lightColorUniform = "lightColor";

    DeferredRenderer::DeferredRenderer(const QSize& size)
        : m_VSSystemUniformBuffer(nullptr)
        , m_VSSystemUniformBufferSize(0)
        , m_PSSystemUniformBuffer(nullptr)
        , m_PSSystemUniformBufferSize(0)
        , m_VSSystemUniformBufferOffsets()
        , m_PSSystemUniformBufferOffsets()
        , m_width(0)
        , m_height(0)
        , m_geometryPassShader(nullptr)
        , m_lightPassShader(nullptr)
        , m_geometryPassMaterial(nullptr)
        , m_lightPassPassMaterial(nullptr)
        , m_screenQuad(nullptr)
    {
        setScreenBufferSize(size.width(), size.height());
        init();
    }
    DeferredRenderer::DeferredRenderer(int width, int height)
        : m_VSSystemUniformBuffer(nullptr)
        , m_VSSystemUniformBufferSize(0)
        , m_PSSystemUniformBuffer(nullptr)
        , m_PSSystemUniformBufferSize(0)
        , m_VSSystemUniformBufferOffsets()
        , m_PSSystemUniformBufferOffsets()
        , m_width(0)
        , m_height(0)
        , m_geometryPassShader(0)
        , m_lightPassShader(0)
        , m_geometryPassMaterial(nullptr)
        , m_lightPassPassMaterial(nullptr)
        , m_screenQuad(nullptr)
    {
        setScreenBufferSize(width, height);
        init();
    }

    void DeferredRenderer::init()
    {
        m_commandQueue.reserve(1000);
        m_lightCommandQueue.reserve(1000);
        //
        // Vertex shader system uniforms
        //
        m_VSSystemUniformBufferSize = sizeof(QMatrix4x4) + sizeof(QMatrix4x4) + sizeof(QVector3D) + sizeof(QMatrix4x4);
        m_VSSystemUniformBuffer = QSharedPointer<uchar>(new uchar[m_VSSystemUniformBufferSize]);
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

        //Set up shaders
        m_geometryPassShader = Shader::createFromFile("shadowShader ",
            "/shaders/advanced_lighting/8.2.g_buffer.vs",
            "/shaders/advanced_lighting/8.2.g_buffer.fs");

        m_geometryPassMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(m_geometryPassShader))));

        m_lightPassShader = Shader::createFromFile("shadowShader ",
            "/shaders/advanced_lighting/8.2.deferred_shading.vs",
            "/shaders/advanced_lighting/8.2.deferred_shading.fs");

        m_lightPassPassMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(m_lightPassShader))));

        m_GBuffer = GBuffer::create(m_screenBufferWidth, m_screenBufferHeight);

        m_screenQuad = MeshFactory::CreateScreenQuad(m_lightPassPassMaterial);
    }

    void DeferredRenderer::begin()
    {
        Renderer::setViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);
        m_commandQueue.clear();
        m_lightCommandQueue.clear();
        m_systemUniforms.clear();

        //test
        if (m_screenSize != m_GBuffer->getSize())
        {
            m_GBuffer.clear();
            m_GBuffer = GBuffer::create(m_screenSize.width(), m_screenSize.height());
        }
    }
    void DeferredRenderer::beginScene(QSharedPointer<Camera> camera)
    {
        memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ProjectionMatrix], &camera->getProjectionMatrix(), sizeof(QMatrix4x4));
        memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ViewMatrix], &camera->getViewMatrix(), sizeof(QMatrix4x4));
        memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_CameraPosition], &camera->getPosition(), sizeof(QVector3D));
        m_lightPassPassMaterial->setUniform("viewPos", camera->getPosition());
    }
    void DeferredRenderer::submit(const RenderCommand& command)
    {
        m_commandQueue.push_back(command);
    }
    void DeferredRenderer::submitMesh(const QSharedPointer<Mesh>& mesh, const QMatrix4x4& transform)
    {
        RenderCommand command;
        command.mesh = mesh;
        command.mesh->setMaterial(m_geometryPassMaterial);
        command.transform = transform;
        command.shader = mesh->getMaterialInstance()->getMaterial()->getShader();
        m_commandQueue.push_back(command);
    }
    void DeferredRenderer::submitLightSetup(const QSharedPointer<LightSetup>& lightSetup)
    {
        auto lights = lightSetup->getLights();

        if (lights.size() > 0)
            m_lightPassPassMaterial->setUniformData("lights", (uchar*)lights.data());

        auto lightEntities = lightSetup->getLightEntities();

        for (int i = 0; i < lightEntities.size(); i++)
        {
            if (lightEntities[i].isNull())
                continue;

            MeshComponent* mesh = lightEntities[i]->getComponent<MeshComponent>();
            if (mesh)
            {
                TransformComponent* tc = lightEntities[i]->getComponent<TransformComponent>();
                if (!tc)
                    qFatal("Mesh does not have transform!"); // Meshes MUST have transforms

                submitLightEntity(mesh->mesh, tc->transform, QVector4D(lights[i].Color, 1.0));
            }
        }
    }

    void DeferredRenderer::submitLightEntity(const QSharedPointer<Mesh>& lightMesh, const QMatrix4x4& transform, const QVector4D& color)
    {
        RenderCommand command;
        command.mesh = lightMesh;
        command.transform = transform;
        command.color = color;
        command.shader = lightMesh->getMaterialInstance()->getMaterial()->getShader();
        m_lightCommandQueue.push_back(command);
    }

    void DeferredRenderer::endScene() {}
    void DeferredRenderer::end() {}
    void DeferredRenderer::flush()
    {
        renderToGBuffer();

        //for (uint i = 0; i < m_commandQueue.size(); i++)
        //{
        //    const RenderCommand& command = m_commandQueue[i];
        //    QSharedPointer<MaterialInstance> material = command.mesh->getMaterialInstance();
        //    int materialRenderFlags = material->getRenderFlags();
        //    Renderer::setDepthTesting((materialRenderFlags & (int)Material::RenderFlags::DISABLE_DEPTH_TEST) == 0);
        //    memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(QMatrix4x4));
        //    setSystemUniforms(command.shader);
        //    command.mesh->render(*this);
        //}
    }
    void DeferredRenderer::close()
    {
        m_commandQueue.clear();
    }

    void DeferredRenderer::setSystemUniforms(QSharedPointer<Shader> shader)
    {
        // TODO: Set per-mesh buffer to slot 1
        shader->setVSSystemUniformBuffer(m_VSSystemUniformBuffer.data(), m_VSSystemUniformBufferSize, 0);
        shader->setPSSystemUniformBuffer(m_PSSystemUniformBuffer.data(), m_PSSystemUniformBufferSize, 0);
    }

    void DeferredRenderer::renderToGBuffer()
    {
        // 1. geometry pass
        m_GBuffer->bind();
        m_GBuffer->clear();

        //for (uint i = 0; i < m_commandQueue.size(); i++)
        //{
        //    RenderCommand command;
        //    command.mesh = QSharedPointer<Mesh>(new Mesh(m_commandQueue[i].mesh));
        //    command.mesh->setMaterial(m_geometryPassMaterial);
        //    command.transform = m_commandQueue[i].transform;
        //    command.shader = m_geometryPassMaterial->getMaterial()->getShader();
        //    Renderer::setDepthTesting(true);
        //    memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(QMatrix4x4));
        //    setSystemUniforms(command.shader);
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

        m_GBuffer->unBind();

        // 2. lighting pass

        //m_GBuffer->bind(0);

        m_lightPassPassMaterial->setTexture("gPosition", m_GBuffer->getTexture(TextureType::Position));
        m_lightPassPassMaterial->setTexture("gNormal", m_GBuffer->getTexture(TextureType::Normal));
        m_lightPassPassMaterial->setTexture("gAlbedoSpec", m_GBuffer->getTexture(TextureType::AlbedoSpec));

        m_screenQuad->render(*this);

        // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
        // ----------------------------------------------------------------------------------
        m_GBuffer->blitDepthBuffer();

        for (uint i = 0; i < m_lightCommandQueue.size(); i++)
        {
            const RenderCommand& command = m_lightCommandQueue[i];
            QSharedPointer<MaterialInstance> material = command.mesh->getMaterialInstance();
            int materialRenderFlags = material->getRenderFlags();
            Renderer::setDepthTesting((materialRenderFlags & (int)Material::RenderFlags::DISABLE_DEPTH_TEST) == 0);
            memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(QMatrix4x4));

            if(command.color != QVector4D())
                material->setUniform(lightColorUniform, command.color);

            setSystemUniforms(command.shader);
            command.mesh->render(*this);
        }
    }
}