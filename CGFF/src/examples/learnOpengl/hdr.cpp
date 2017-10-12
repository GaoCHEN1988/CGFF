#include "hdr.h"

namespace LearnGL {

    using namespace CGFF;

    static QSharedPointer<Shader>  g_shader;
    static QSharedPointer<Texture2D> woodTexture;
    static QVector3D g_CubeTransform(0.0f, 0.0f, 25.0f);

    struct HdrLight
    {
        QVector3D Position;
        QVector3D Color;
    };

    QVector<HdrLight> g_lights;

    HDR::HDR(const QSharedPointer<CGFF::Scene>& scene)
        :m_scene(scene)
        , m_cube(nullptr)
    {

    }
    HDR::~HDR()
    {}

    void HDR::init()
    {
        g_shader = Shader::createFromFile("shadowShader ",
            "/shaders/advanced_lighting/6.lighting.vs",
            "/shaders/advanced_lighting/6.lighting.fs");

        woodTexture = Texture2D::createFromFile("Wood", "/resource/LearnOpenGL/textures/wood.png");

        m_objectMaterialInstance = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<CGFF::Material>(new Material(g_shader))));
        m_objectMaterialInstance->setTexture("diffuseTexture", woodTexture);

        QMatrix4x4 trans_cube;
        trans_cube.scale(2.5f, 2.5f, 20.0f);
        m_cube = QSharedPointer<Entity>(new Entity(LearnGL::CreateCube(5,
            m_objectMaterialInstance), trans_cube));

        m_scene->add(m_cube);

        g_lights.push_back({ QVector3D(0.0f, 5.0f, 49.0f), QVector3D(200.0f, 200.0f, 200.0f) });
        g_lights.push_back({ QVector3D(0.0f, 1.0f, 10.0f), QVector3D(0.6f, 0.0f, 0.0f) });
        g_lights.push_back({ QVector3D(0.0f, 1.0f, 20.0f), QVector3D(0.0f, 0.0f, 0.5f) });
        g_lights.push_back({ QVector3D(0.0f, 1.0f, 40.0f), QVector3D(0.0f, 0.2f, 0.0f) });

    }
    void HDR::render()
    {
        m_objectMaterialInstance->setUniform("viewPos", m_scene->getCamera()->getPosition());
        m_objectMaterialInstance->setUniformData("lights", (uchar*)g_lights.data());
        m_objectMaterialInstance->setUniform("inverse_normals", true);
    }

}