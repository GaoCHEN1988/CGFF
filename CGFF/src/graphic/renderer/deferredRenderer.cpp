#include "deferredRenderer.h"
#include "renderer.h"
#include "graphic/meshFactory.h"
#include <random>

namespace CGFF {

    const QString lightColorUniform = "lightColor";
    static float lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }

    static QSharedPointer<Shader> g_shaderSSAO;
    static QSharedPointer<Shader> g_shaderSSAOBlur;

    static TextureParameters ssaoParams;
    static TextureParameters noiseTexParams;

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
            "/shaders/advanced_lighting/9.ssao_geometry.vs",
            "/shaders/advanced_lighting/9.ssao_geometry.fs");

        m_geometryPassMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(m_geometryPassShader))));

        m_lightPassShader = Shader::createFromFile("shadowShader ",
            "/shaders/advanced_lighting/9.ssao.vs",
            "/shaders/advanced_lighting/9.ssao_lighting.fs");

        m_lightPassPassMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(m_lightPassShader))));

        m_GBuffer = GBuffer::create(m_screenBufferWidth, m_screenBufferHeight);

        //m_screenQuad = MeshFactory::CreateScreenQuad(m_lightPassPassMaterial);

#ifdef TEST_SSAO

        
        ssaoParams.gl_textureFormat = QOpenGLTexture::R32F;
        ssaoParams.gl_pixelFormat = QOpenGLTexture::PixelFormat::RGB;
        ssaoParams.gl_pixelType = QOpenGLTexture::PixelType::Float32;
        ssaoParams.gl_filter = QOpenGLTexture::Filter::Nearest;
        m_ssaoFB = Framebuffer2D::create(m_screenBufferWidth, m_screenBufferHeight, ssaoParams);
        m_ssaoBlurFB = Framebuffer2D::create(m_screenBufferWidth, m_screenBufferHeight, ssaoParams);

        g_shaderSSAO = Shader::createFromFile("ssaoShader ",
            "/shaders/advanced_lighting/9.ssao.vs",
            "/shaders/advanced_lighting/9.ssao.fs");

        m_shaderSSAOMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(g_shaderSSAO))));

        g_shaderSSAOBlur = Shader::createFromFile("ssaoBlurShader ",
            "/shaders/advanced_lighting/9.ssao.vs",
            "/shaders/advanced_lighting/9.ssao_blur.fs");

        m_shaderSSAOBlurMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(g_shaderSSAOBlur))));

        m_screenQuad = MeshFactory::CreateScreenQuad(m_shaderSSAOMaterial);

        std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
        std::default_random_engine generator;
        
        for (unsigned int i = 0; i < 64; ++i)
        {
            QVector3D sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
            sample.normalize();
            sample *= randomFloats(generator);
            float scale = float(i) / 64.0;

            // scale samples s.t. they're more aligned to center of kernel
            scale = lerp(0.1f, 1.0f, scale * scale);
            sample *= scale;
            m_ssaoKernel.push_back(sample);
        }

        // generate noise texture
        // ----------------------
        QVector<QVector3D> ssaoNoise;
        for (unsigned int i = 0; i < 16; i++)
        {
            QVector3D noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
            ssaoNoise.push_back(noise);
        }

        
        noiseTexParams.gl_textureFormat = QOpenGLTexture::RGB32F;
        noiseTexParams.gl_pixelFormat = QOpenGLTexture::PixelFormat::RGB;
        noiseTexParams.gl_pixelType = QOpenGLTexture::PixelType::Float32;
        noiseTexParams.gl_filter = QOpenGLTexture::Filter::Nearest;
        noiseTexParams.gl_wrap = QOpenGLTexture::WrapMode::Repeat;

        m_noiseTexture = Texture2D::create(4, 4, &ssaoNoise[0], noiseTexParams);
#endif

    }

    void DeferredRenderer::begin()
    {
        Renderer::setViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);
        m_commandQueue.clear();
        m_lightCommandQueue.clear();
        m_systemUniforms.clear();

        if (m_screenSize != m_GBuffer->getSize())
        {
            m_GBuffer.clear();
            m_GBuffer = GBuffer::create(m_screenSize.width(), m_screenSize.height());
        }

#ifdef TEST_SSAO
        if (m_screenSize != m_ssaoFB->getSize())
        {
            m_ssaoFB.clear();
            m_ssaoFB = Framebuffer2D::create(m_screenSize.width(), m_screenSize.height(), ssaoParams);

            m_ssaoBlurFB.clear();
            m_ssaoBlurFB = Framebuffer2D::create(m_screenSize.width(), m_screenSize.height(), ssaoParams);
        }

#endif
    }
    void DeferredRenderer::beginScene(QSharedPointer<Camera> camera)
    {
        memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ProjectionMatrix], &camera->getProjectionMatrix(), sizeof(QMatrix4x4));
        memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ViewMatrix], &camera->getViewMatrix(), sizeof(QMatrix4x4));
        memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_CameraPosition], &camera->getPosition(), sizeof(QVector3D));
#ifdef TEST_SSAO
        m_shaderSSAOMaterial->setUniform("projection", camera->getProjectionMatrix());
#else
        m_lightPassPassMaterial->setUniform("viewPos", camera->getPosition());

#endif
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

        for(int i = 0; i < lights.size(); i++)
        {
            m_lightsArray.append(*lights[i]);

        }
        
        if(!m_lightsArray.isEmpty())
            m_lightPassPassMaterial->setUniformData("lights", (uchar*)m_lightsArray.data());

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

                submitLightEntity(mesh->mesh, tc->getTransform(), lights[i]->color);
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

#ifdef TEST_SSAO

        m_ssaoFB->bind();
        Renderer::clear(RendererBufferType::RENDERER_BUFFER_COLOR);
        m_shaderSSAOMaterial->setUniformData("samples", (uchar*)m_ssaoKernel.data());
        m_shaderSSAOMaterial->setTexture("gPosition", m_GBuffer->getTexture(TextureType::Position));
        m_shaderSSAOMaterial->setTexture("gNormal", m_GBuffer->getTexture(TextureType::Normal));
        m_shaderSSAOMaterial->setTexture("texNoise", m_noiseTexture);
        m_screenQuad->render(*this);
        m_ssaoFB->unBind();

        m_screenQuad->setMaterial(m_shaderSSAOBlurMaterial);
        m_ssaoBlurFB->bind();
        Renderer::clear(RendererBufferType::RENDERER_BUFFER_COLOR);
        m_shaderSSAOBlurMaterial->setTexture("ssaoInput", m_ssaoFB->getTexture());
        m_screenQuad->render(*this);
        m_ssaoBlurFB->unBind();
        
        m_screenQuad->setMaterial(m_lightPassPassMaterial);
#endif
        //lighting pass
        m_lightPassPassMaterial->setTexture("gPosition", m_GBuffer->getTexture(TextureType::Position));
        m_lightPassPassMaterial->setTexture("gNormal", m_GBuffer->getTexture(TextureType::Normal));
        m_lightPassPassMaterial->setTexture("gAlbedoSpec", m_GBuffer->getTexture(TextureType::AlbedoSpec));
#ifdef TEST_SSAO
        m_lightPassPassMaterial->setTexture("ssao", m_ssaoBlurFB->getTexture());
#endif
        m_screenQuad->render(*this);

        //copy content of geometry's depth buffer to default framebuffer's depth buffer
        // ----------------------------------------------------------------------------------
        m_GBuffer->blitDepthBuffer();
        for (uint i = 0; i < m_lightCommandQueue.size(); i++)
        {
            const RenderCommand& command = m_lightCommandQueue[i];
            QSharedPointer<MaterialInstance> material = command.mesh->getMaterialInstance();
            int materialRenderFlags = material->getRenderFlags();
            Renderer::setDepthTesting((materialRenderFlags & (int)Material::RenderFlags::DISABLE_DEPTH_TEST) == 0);
            memcpy(m_VSSystemUniformBuffer.data() + m_VSSystemUniformBufferOffsets[VSSystemUniformIndex_ModelMatrix], &command.transform, sizeof(QMatrix4x4));

            if (command.color != QVector4D())
                material->setUniform(lightColorUniform, command.color);

            setSystemUniforms(command.shader);
            command.mesh->render(*this);
        }
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
    }
}