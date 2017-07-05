#include "test3DLayer.h"

namespace CGFF {

    Test3DLayer::Test3DLayer()
        : Layer3D(QSharedPointer<CGFF::Scene>(new CGFF::Scene()))
    {
    }

    void Test3DLayer::init()
    {
        m_shader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);

#ifdef OPENGL_ES

#else
        // load and compile vertex shader
        bool success = m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader/sceneShader.vert");
        // load and compile fragment shader
        success = m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader/sceneShader.frag");
#endif

        m_shader->link();

        m_material = QSharedPointer<CGFF::Material>(new CGFF::Material(m_shader));

        m_model_cube = QSharedPointer<CGFF::Model>(new CGFF::Model("Resources/Cube.obj", QSharedPointer<CGFF::MaterialInstance>(new CGFF::MaterialInstance(m_material))));
        m_model_sphere = QSharedPointer<CGFF::Model>(new CGFF::Model("Resources/Sphere.obj", QSharedPointer<CGFF::MaterialInstance>(new CGFF::MaterialInstance(m_material))));

        m_cube = QSharedPointer<CGFF::Entity>(new CGFF::Entity());
        m_cube->addComponent(QSharedPointer<CGFF::Component>(new CGFF::MeshComponent(m_model_cube->getMesh())));
        m_cube->addComponent(QSharedPointer<CGFF::Component>(new CGFF::TransformComponent(QMatrix4x4())));

        m_sphere = QSharedPointer<CGFF::Entity>(new CGFF::Entity());
        m_sphere->addComponent(QSharedPointer<CGFF::Component>(new CGFF::MeshComponent(m_model_sphere->getMesh())));
        m_sphere->addComponent(QSharedPointer<CGFF::Component>(new CGFF::TransformComponent(QMatrix4x4())));

        m_plane_mesh.create(32, 32, QVector3D(0, 1, 0), QSharedPointer<CGFF::MaterialInstance>(new CGFF::MaterialInstance(m_material)));
        m_plane = QSharedPointer<CGFF::Entity>(new CGFF::Entity());
        m_plane->addComponent(QSharedPointer<CGFF::Component>(new CGFF::MeshComponent(m_plane_mesh.mesh)));
        m_plane->addComponent(QSharedPointer<CGFF::Component>(new CGFF::TransformComponent(QMatrix4x4())));

        Layer3D::getScene()->add(m_cube);
        Layer3D::getScene()->add(m_sphere);
        Layer3D::getScene()->add(m_plane);
    }

    void Test3DLayer::render()
    {
        m_ml_matrix.rotate(m_Rotation, QVector3D(1, 1, 0));

        CGFF::TransformComponent* cubeTransform = m_cube->getComponent<TransformComponent>();
        CGFF::TransformComponent* sphereTransform = m_sphere->getComponent<TransformComponent>();

        QMatrix4x4 m;
        m.translate(QVector3D(-4, 0, 0));
        QMatrix4x4 m2;
        m2.translate(QVector3D(4, 0, 0));

        cubeTransform->transform = m*m_ml_matrix;
        sphereTransform->transform = m2*m_ml_matrix;

        m_Rotation += 0.5f;

        Layer3D::render();

        GLenum error = CGFF::GL->glGetError();
        if (error != GL_NO_ERROR)
        {
            //To do: show error in logging system
            qFatal("Opengl error!");
        }
    }

    void Test3DLayer::resize(int width, int height) 
    {
        CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        Layer3D::getScene()->getCamera()->resize(width, height);
    }

    void Test3DLayer::mousePressEvent(QMouseEvent *event)
    {
        Layer3D::getScene()->getCamera()->mousePressEvent(event);
    }
    void Test3DLayer::mouseMoveEvent(QMouseEvent *event)
    {
        Layer3D::getScene()->getCamera()->mouseMoveEvent(event);
    }

    void Test3DLayer::mouseReleaseEvent(QMouseEvent *event) 
    {
        Layer3D::getScene()->getCamera()->mousePressEvent(event);
    }

    void Test3DLayer::keyPressEvent(QKeyEvent *event) 
    {
        
    }
}