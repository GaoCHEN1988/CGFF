#include "normalMapping.h"

namespace LearnGL {

    using namespace CGFF;

    static QSharedPointer<Shader>  normalMappingShader;
    static QSharedPointer<Texture2D> diffuseMap;
    static QSharedPointer<Texture2D> normalMap;
    static QVector3D g_LightPos(0.0, 10.0, 0.0);

    NormalMapping::NormalMapping(const QSharedPointer<CGFF::Scene>& scene)
        :m_scene(scene)
    {

    }
    NormalMapping::~NormalMapping()
    {}

    void NormalMapping::init()
    {
        normalMappingShader = Shader::createFromFile("NormalMappingShader ",
            "/shaders/advanced_lighting/4.normal_mapping.vs",
            "/shaders/advanced_lighting/4.normal_mapping.fs");

        diffuseMap = Texture2D::createFromFile("DiffuseMap", "/resource/LearnOpenGL/textures/brickwall.jpg");
        normalMap = Texture2D::createFromFile("NormalMap", "/resource/LearnOpenGL/textures/brickwall_normal.jpg");

        m_objectMaterialInstance = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<CGFF::Material>(new Material(normalMappingShader))));
        m_objectMaterialInstance->setTexture("diffuseMap", diffuseMap);
        m_objectMaterialInstance->setTexture("normalMap", normalMap);

        m_plane = QSharedPointer<Entity>(new Entity(MeshFactory::CreatePlane(
            128, 128, QVector3D(0, 1, 0),
            m_objectMaterialInstance)));

        m_scene->add("Plane", m_plane);

    }
    void NormalMapping::render()
    {
        m_objectMaterialInstance->setUniform("viewPos", m_scene->getCamera()->getPosition());
        m_objectMaterialInstance->setUniform("lightPos", g_LightPos);
    }

}