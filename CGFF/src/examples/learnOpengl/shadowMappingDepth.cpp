#include "shadowMappingDepth.h"

namespace LearnGL {
    using namespace CGFF;

    QSharedPointer<Shader> shadowPassShader;
    QSharedPointer<FramebufferDepth> g_DepthBuffer;
    QSharedPointer<TextureDepth> g_ShadowMap;

    QSharedPointer<Shader>  simpleDepthShader;
    QSharedPointer<Shader>  debugDepthQuad;

    QSharedPointer<Texture2D> woodTexture;

    ShadowMappingDepth::ShadowMappingDepth()
    {
    }


    ShadowMappingDepth::~ShadowMappingDepth()
    {
    }

    void ShadowMappingDepth::init(QSize size)
    {
        QStringList skybox_files =
        {
            "/resource/skybox/sky_xp.jpg",
            "/resource/skybox/sky_xn.jpg",
            "/resource/skybox/sky_yp.jpg",
            "/resource/skybox/sky_yn.jpg",
            "/resource/skybox/sky_zp.jpg",
            "/resource/skybox/sky_zn.jpg"
        };

        simpleDepthShader = Shader::createFromFile("SimpleDepthShader ",
            "/shaders/advanced_lighting/3.1.1.shadow_mapping_depth.vs",
            "/shaders/advanced_lighting/3.1.1.shadow_mapping_depth.fs");

        debugDepthQuad = Shader::createFromFile("SimpleDepthShader ",
            "/shaders/advanced_lighting/3.1.1.debug_quad.vs",
            "/shaders/advanced_lighting/3.1.1.debug_quad_depth.fs");

        woodTexture = Texture2D::createFromFile("/resource/LearnOpenGL/textures/wood.png");
    
        m_depthmap = FramebufferDepth::create(size.width(), size.height());

        m_lights = QSharedPointer<LightSetup>(new LightSetup());
        QSharedPointer<Light> light = QSharedPointer<Light>(new Light(QVector3D(-2.0f, 4.0f, -1.0f)));
        m_lights->add(light);
    }

    void ShadowMappingDepth::render()
    {
        CGFF::Renderer::clear(RENDERER_BUFFER_DEPTH | RENDERER_BUFFER_COLOR);
    }

}