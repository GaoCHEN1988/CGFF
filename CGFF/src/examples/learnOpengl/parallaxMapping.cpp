#include "parallaxMapping.h"

namespace LearnGL {

    using namespace CGFF;

    static QSharedPointer<Shader>  parallaxMappingShader;
    static QSharedPointer<Texture2D> diffuseMap;
    static QSharedPointer<Texture2D> normalMap;
    static QSharedPointer<Texture2D> heightMap;
    static QVector3D g_LightPos(50.0, 10.0, -30.0);

    ParallaxMapping::ParallaxMapping(const QSharedPointer<CGFF::Scene>& scene)
        :m_scene(scene)
    {

    }
    ParallaxMapping::~ParallaxMapping()
    {}

    void ParallaxMapping::init()
    {

        parallaxMappingShader = Shader::createFromFile("parallaxMappingShader",
            "/shaders/advanced_lighting/5.3.parallax_mapping.vs",
            "/shaders/advanced_lighting/5.3.parallax_mapping.fs");

        diffuseMap = Texture2D::createFromFile("DiffuseMap", "/resource/LearnOpenGL/textures/bricks2.jpg");
        normalMap = Texture2D::createFromFile("NormalMap", "/resource/LearnOpenGL/textures/bricks2_normal.jpg");
        heightMap = Texture2D::createFromFile("HeightMap", "/resource/LearnOpenGL/textures/bricks2_disp.jpg");

        m_objectMaterialInstance = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<CGFF::Material>(new Material(parallaxMappingShader))));
        m_objectMaterialInstance->setTexture("diffuseMap", diffuseMap);
        m_objectMaterialInstance->setTexture("normalMap", normalMap);
        m_objectMaterialInstance->setTexture("depthMap", heightMap);

        m_plane = QSharedPointer<Entity>(new Entity(LearnGL::CreatePlane(
            128, 128, QVector3D(0, 1, 0),
            m_objectMaterialInstance)));

        m_scene->add("Plane", m_plane);
    }

    void ParallaxMapping::render()
    {
        Renderer::setDepthTesting(true);
        m_objectMaterialInstance->setUniform("viewPos", m_scene->getCamera()->getPosition());
        m_objectMaterialInstance->setUniform("lightPos", g_LightPos);
        m_objectMaterialInstance->setUniform("heightScale", 0.5);
    }

}