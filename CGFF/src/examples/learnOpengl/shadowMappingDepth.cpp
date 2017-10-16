#include "shadowMappingDepth.h"

namespace LearnGL {
    using namespace CGFF;

    static QSharedPointer<Shader>  shadowShader;
    static QSharedPointer<Shader>  debugDepthQuadShader;
    static QSharedPointer<Texture2D> woodTexture;
    static QVector3D g_CubeTransform(0, 10.0, 0);
    static QVector3D g_LightPos(50.0, 50.0, 50.0);

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

        shadowShader = Shader::createFromFile("shadowShader ",
            "/shaders/advanced_lighting/3.1.3.shadow_mapping.vs",
            "/shaders/advanced_lighting/3.1.3.shadow_mapping.fs");

        woodTexture = Texture2D::createFromFile("Wood", "/resource/LearnOpenGL/textures/wood.png");

        m_objectMaterialInstance = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<CGFF::Material>(new Material(shadowShader))));
        m_objectMaterialInstance->setTexture("diffuseTexture", woodTexture);

        m_plane = QSharedPointer<Entity>(new Entity(LearnGL::CreatePlane(
            128, 128, QVector3D(0, 1, 0),
            m_objectMaterialInstance)));

        m_scene->add(m_plane);

        QMatrix4x4 trans_cube;
        trans_cube.translate(g_CubeTransform);
        m_cube = QSharedPointer<Entity>(new Entity(LearnGL::CreateCube(5,
            m_objectMaterialInstance), trans_cube)) ;

        m_scene->add(m_cube);

        trans_cube.setToIdentity();
        trans_cube.translate(QVector3D(10.0, 20.0, 0));
        m_cube2 = QSharedPointer<Entity>(new Entity(LearnGL::CreateCube(5,
            m_objectMaterialInstance), trans_cube));

        m_scene->add(m_cube2);
    }

    void ShadowMappingDepth::render()
    {
        //m_objectMaterialInstance->setUniform("lightPos", g_LightPos);
        m_objectMaterialInstance->setUniform("viewPos", m_scene->getCamera()->getPosition());
    }

}