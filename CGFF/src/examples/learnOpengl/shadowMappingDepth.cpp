#include "shadowMappingDepth.h"

namespace LearnGL {
    using namespace CGFF;

    QSharedPointer<Shader> shadowPassShader;
    QSharedPointer<FramebufferDepth> g_DepthBuffer;
    QSharedPointer<TextureDepth> g_ShadowMap;

    QSharedPointer<Shader>  simpleDepthShader;
    QSharedPointer<Shader>  shadowShader;
    QSharedPointer<Shader>  debugDepthQuadShader;

    QSharedPointer<Texture2D> woodTexture;

    QVector3D g_CubeTransform(40, 10, 0);

    GLfloat near_plane = 1.0f, far_plane = 7.5f;

    QMatrix4x4 lightSpaceMatrix;

    ShadowMappingDepth::ShadowMappingDepth(const QSharedPointer<Scene>& scene)
        : m_scene(scene)
    {
    }


    ShadowMappingDepth::~ShadowMappingDepth()
    {
    }

    void ShadowMappingDepth::init()
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

        //simpleDepthShader = Shader::createFromFile("SimpleDepthShader ",
        //    "/shaders/advanced_lighting/3.1.1.shadow_mapping_depth.vs",
        //    "/shaders/advanced_lighting/3.1.1.shadow_mapping_depth.fs");

        shadowShader = Shader::createFromFile("shadowShader ",
            "/shaders/advanced_lighting/3.1.2.shadow_mapping.vs",
            "/shaders/advanced_lighting/3.1.2.shadow_mapping.fs");

        simpleDepthShader = Shader::createFromFile("SimpleDepthShader ",
            "/shaders/advanced_lighting/3.1.2.shadow_mapping_depth.vs",
            "/shaders/advanced_lighting/3.1.2.shadow_mapping_depth.fs");

        woodTexture = Texture2D::createFromFile("/resource/LearnOpenGL/textures/wood.png");

        m_lights = QSharedPointer<LightSetup>(new LightSetup());
        QSharedPointer<Light> light = QSharedPointer<Light>(new Light(QVector3D(0.8f, 0.8f, 0.8f)));
        light->position = QVector3D(-2.0f, 4.0f, -1.0f);
        light->projection.ortho(0, (float)m_scene->getSize().width(), 0, (float)m_scene->getSize().height(), near_plane, far_plane);
        light->view.lookAt(light->position, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
        lightSpaceMatrix = light->projection * light->view;
        m_lights->add(light);

        m_scene->pushLightSetup(m_lights);

        m_depthMaterial = QSharedPointer<CGFF::Material>(new Material(simpleDepthShader));

        m_plane = QSharedPointer<Entity>(new Entity(LearnGL::CreatePlane(128, 128, QVector3D(0, 1, 0),
            QSharedPointer<MaterialInstance>(new MaterialInstance(m_depthMaterial)))));

        m_scene->add(m_plane);

        QMatrix4x4 trans_cube;
        trans_cube.translate(g_CubeTransform);
        m_cube = QSharedPointer<Entity>(new Entity(LearnGL::CreateCube(5,
            QSharedPointer<MaterialInstance>(new MaterialInstance(m_depthMaterial))), trans_cube)) ;

        m_scene->add(m_cube);
    }

    void ShadowMappingDepth::render()
    {
        CGFF::Renderer::clear(RENDERER_BUFFER_DEPTH | RENDERER_BUFFER_COLOR);

        m_depthMaterial->setUniform("lightSpaceMatrix", lightSpaceMatrix);
    }

}