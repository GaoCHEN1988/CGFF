#include "ssao.h"

namespace LearnGL {

    using namespace CGFF;

    static QSharedPointer<LightSetup> g_lights;

    static float linear = 0.01;
    static float quadratic = 0.01;

    SSAO::SSAO(const QSharedPointer<CGFF::Scene>& scene)
        :m_scene(scene)
    {

    }
    SSAO::~SSAO()
    {}

    void SSAO::init()
    {
        m_objectModel = QSharedPointer<Model>(new Model("/resource/LearnOpenGL/objects/nanosuit/nanosuit.obj", nullptr));

        for (const QSharedPointer<Mesh>& mesh : m_objectModel->getMeshes())
        {
            QMatrix4x4 trans;
            trans.translate(0.0, 5.0, 0.0);
            trans.rotate(-90.0f, 1.0, 0.0, 0.0);
            QSharedPointer<CGFF::Entity> objectEntity =
                QSharedPointer<Entity>(new Entity(mesh, trans));
            m_scene->add(objectEntity);
        }

        QMatrix4x4 trans_cube;
        trans_cube.scale(7.5f, 7.5f, 7.0f);
        QSharedPointer<Mesh> meshCube = LearnGL::CreateCube(5, nullptr);
        meshCube->setInvertedNormal(true);
        m_cube = QSharedPointer<Entity>(new Entity(meshCube, trans_cube));

        m_scene->add(m_cube);

        //Set lights
        g_lights = QSharedPointer<LightSetup>(new LightSetup());

        //g_lights->add({ QVector3D(20.0, 8.0, -5.0), QVector3D(0.4, 0.4, 0.7), linear, quadratic });

        m_scene->pushLightSetup(g_lights);

    }
    void SSAO::render()
    {}

}