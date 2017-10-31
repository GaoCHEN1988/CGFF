#include "pbr.h"

namespace LearnGL {

    using namespace CGFF;

    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 8;
    static QSharedPointer<Shader>  g_shader;

    struct PbrLight
    {
        QVector3D Position;
        QVector3D Color;
    };

    static QVector<PbrLight> g_lights;

    static QSharedPointer<Texture2D> albedo;
    static QSharedPointer<Texture2D> normal;
    static QSharedPointer<Texture2D> metallic;
    static QSharedPointer<Texture2D> roughness;
    static QSharedPointer<Texture2D> ao;

    PBR::PBR(const QSharedPointer<CGFF::Scene>& scene)
        :m_scene(scene)
    {

    }
    PBR::~PBR()
    {}

    void PBR::init()
    {
        g_shader = Shader::createFromFile("Shadder ",
            "/shaders/pbr/1.2.pbr.vs",
            "/shaders/pbr/1.2.pbr.fs");

        albedo = Texture2D::createFromFile("albedo", "/resource/LearnOpenGL/textures/pbr/rusted_iron/albedo.png");
        normal = Texture2D::createFromFile("normal", "/resource/LearnOpenGL/textures/pbr/rusted_iron/normal.png");
        metallic = Texture2D::createFromFile("metallic", "/resource/LearnOpenGL/textures/pbr/rusted_iron/metallic.png");
        roughness = Texture2D::createFromFile("roughness", "/resource/LearnOpenGL/textures/pbr/rusted_iron/roughness.png");
        ao = Texture2D::createFromFile("ao", "/resource/LearnOpenGL/textures/pbr/rusted_iron/ao.png");

        //m_objectMaterialInstance = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<CGFF::Material>(new Material(g_shader))));

        g_lights.push_back({ QVector3D(-10.0f,  10.0f, 10.0f), QVector3D(300.0f, 300.0f, 300.0f) });
        g_lights.push_back({ QVector3D(10.0f,  10.0f, 10.0f), QVector3D(300.0f, 300.0f, 300.0f) });
        g_lights.push_back({ QVector3D(-10.0f, -10.0f, 10.0f), QVector3D(300.0f, 300.0f, 300.0f) });
        g_lights.push_back({ QVector3D(10.0f, -10.0f, 10.0f), QVector3D(300.0f, 300.0f, 300.0f) });
        
        //m_sphereMesh = LearnGL::CreateSphere(64, 64, nullptr);

        m_sphereModel = QSharedPointer<Model>(new Model("/resource/SphereHighPoly.obj", nullptr));

        for (unsigned int row = 0; row < nrRows; ++row)
        {
            for (unsigned int col = 0; col < nrColumns; ++col)
            {
                QSharedPointer<MaterialInstance> material = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<CGFF::Material>(new Material(g_shader))));
                material->setTexture("albedoMap", albedo);
                material->setTexture("normalMap", normal);
                material->setTexture("metallicMap", metallic);
                material->setTexture("roughnessMap", roughness);
                material->setTexture("aoMap", ao);

                //material->setUniform("metallic", (float)row / (float)nrRows);
                //material->setUniform("albedo", QVector3D(0.5f, 0.0f, 0.0f));
                //material->setUniform("ao", 1.0f);

                //// we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
                //// on direct lighting.
                //material->setUniform("roughness", qBound((float)col / (float)nrColumns, 0.025f, 1.0f));
                
                material->setUniformData("lights", (uchar*)g_lights.data());

                QMatrix4x4 trans;
                trans.translate(QVector3D(
                    (float)(col - (nrColumns / 2)) * spacing,
                    (float)(row - (nrRows / 2)) * spacing,
                    0.0f
                    ));
                
                int count = 0;
                for (const QSharedPointer<Mesh>& mesh : m_sphereModel->getMeshes())
                {
                    count++;
                    mesh->setMaterial(material);

                    QSharedPointer<CGFF::Entity> objectEntity =
                        QSharedPointer<Entity>(new Entity(mesh, trans));

                    QString name = "ObjectEntity" + QString::number(row)+ QString::number(col) + "_" + QString::number(count);

                    m_scene->add(name, objectEntity);
                }
            }
        }
    }
    void PBR::render()
    {
    }

}