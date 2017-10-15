#include "deferredShading.h"
#include "graphic/lightSetup.h"

namespace LearnGL {

    using namespace CGFF;

    static QSharedPointer<Shader>  g_shaderLightBox;
    static QVector<QVector3D> g_objectPositions;
    const unsigned int NR_LIGHTS = 32;

    QSharedPointer<LightSetup> g_lights;

    DeferredShading::DeferredShading(const QSharedPointer<CGFF::Scene>& scene)
        :m_scene(scene)
    {

    }
    DeferredShading::~DeferredShading()
    {}

    void DeferredShading::init()
    {
        m_objectModel = QSharedPointer<Model>(new Model("/resource/LearnOpenGL/objects/nanosuit/nanosuit.obj", nullptr));

        //Set object positions
        g_objectPositions.push_back(QVector3D(-20.0, 0.0, -20.0));
        g_objectPositions.push_back(QVector3D(0.0, 0.0, -20.0));
        g_objectPositions.push_back(QVector3D(20.0, 0.0, -20.0));
        g_objectPositions.push_back(QVector3D(-20.0, 0.0, 0.0));
        g_objectPositions.push_back(QVector3D(0.0, 0.0, 0.0));
        g_objectPositions.push_back(QVector3D(20.0, 0.0, 0.0));
        g_objectPositions.push_back(QVector3D(-20.0, 0.0, 20.0));
        g_objectPositions.push_back(QVector3D(0.0, 0.0, 20.0));
        g_objectPositions.push_back(QVector3D(20.0, 0.0, 20.0));

        for (int i = 0; i < g_objectPositions.size(); i++)
        {
            QMatrix4x4 trans;
            trans.translate(g_objectPositions[i]);

            for (const QSharedPointer<Mesh>& mesh : m_objectModel->getMeshes())
            {
                QSharedPointer<CGFF::Entity> objectEntity =
                    QSharedPointer<Entity>(new Entity(mesh, trans));
                m_scene->add(objectEntity);

            }

        }

        g_shaderLightBox = Shader::createFromFile("LightBoxShader",
            "/shaders/advanced_lighting/8.2.deferred_light_box.vs",
            "/shaders/advanced_lighting/8.2.deferred_light_box.fs");

        m_lightBoxMaterial = QSharedPointer<MaterialInstance>(
            new MaterialInstance(QSharedPointer<Material>(new Material(g_shaderLightBox))));

        QSharedPointer<Mesh> cubeMesh = LearnGL::CreateCube(2, m_lightBoxMaterial);

        //Set lights
        g_lights = QSharedPointer<LightSetup>(new LightSetup());
        qsrand(13);
        const float constant = 1.0; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
        const float linear = 0.7;
        const float quadratic = 0.1;

        for (unsigned int i = 0; i < NR_LIGHTS; i++)
        {
            // calculate slightly random offsets
            float xPos = ((qrand() % 100) / 100.0) * 40.0 - 20.0;
            float yPos = ((qrand() % 100) / 100.0) * 20.0;
            float zPos = ((qrand() % 100) / 100.0) * 40.0 - 20.0;
            // also calculate random color
            float rColor = ((qrand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
            float gColor = ((qrand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
            float bColor = ((qrand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0

            const float maxBrightness = qMax(qMax(rColor, gColor), bColor);
            float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);

            QMatrix4x4 tmpTrans;
            tmpTrans.translate(QVector3D(xPos, yPos, zPos));

            QSharedPointer<Entity> lightEntity = QSharedPointer<Entity>(new Entity(cubeMesh, tmpTrans));

            g_lights->add({ QVector3D(xPos, yPos, zPos), QVector3D(rColor, gColor, bColor), linear, quadratic, radius }
            , lightEntity);

        }

        m_scene->pushLightSetup(g_lights);
    }

    void DeferredShading::render()
    {

    }

}