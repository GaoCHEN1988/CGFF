#include "examples/test3D.h"
#include <QKeyEvent>

using namespace CGFF;

Test3D::Test3D(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_Rotation(0.0)
{
    setFocusPolicy(Qt::ClickFocus);
}

void Test3D::initializeGL() 
{
#ifdef OPENGL_ES
#else
    QSurfaceFormat qFormat = QOpenGLWidget::format();
    qFormat.setProfile(QSurfaceFormat::CoreProfile);
    qFormat.setVersion(4, 4);
    QOpenGLContext::currentContext()->setFormat(qFormat);
#endif

    // initialize OpenGL
    CGFF::GL = QOpenGLContext::currentContext()->functions();
    CGFF::GL->initializeOpenGLFunctions();

    //Init
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

    m_Sphere = QSharedPointer<CGFF::Entity>(new CGFF::Entity());
    m_Sphere->addComponent(QSharedPointer<CGFF::Component>(new CGFF::MeshComponent(m_model_sphere->getMesh())));
    m_Sphere->addComponent(QSharedPointer<CGFF::Component>(new CGFF::TransformComponent(QMatrix4x4())));
 
    m_layer = QSharedPointer<CGFF::Layer3D>(new CGFF::Layer3D(
        QSharedPointer<CGFF::Scene>(new CGFF::Scene())));

    if (m_model_sphere->getMesh() != nullptr)
        m_layer->GetScene()->add(m_cube);

    if(m_model_cube->getMesh() != nullptr)
        m_layer->GetScene()->add(m_Sphere);

    m_UnSetUniforms[0] = true;
    m_UnSetUniforms[1] = true;
}

void Test3D::paintGL() 
{
    CGFF::GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CGFF::GL->glEnable(GL_BLEND);
    CGFF::GL->glEnable(GL_DEPTH_TEST);
    CGFF::GL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_ml_matrix.rotate(m_Rotation, QVector3D(1, 1, 0));

    CGFF::TransformComponent* cubeTransform = m_cube->getComponent<TransformComponent>();
    CGFF::TransformComponent* sphereTransform = m_Sphere->getComponent<TransformComponent>();

    QMatrix4x4 m;
    m.translate(QVector3D(-4, 0, 0));
    QMatrix4x4 m2;
    m2.translate(QVector3D(4, 0, 0));

    cubeTransform->transform = m*m_ml_matrix;
    sphereTransform->transform = m2*m_ml_matrix;

    m_Rotation += 0.5f;
    
    m_layer->render();

    GLenum error = CGFF::GL->glGetError();
    if (error != GL_NO_ERROR)
    {
        //To do: show error in logging system
        qFatal("Opengl error!");
    }
}

void Test3D::resizeGL(int width, int height) 
{
    CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    m_pr_matrix.setToIdentity();
    m_pr_matrix.perspective(45.0f, GLfloat(width) / GLfloat(height), 0.01f, 1000.0f);
    //m_material->setUniform("pr_matrix", m_pr_matrix);
}
void Test3D::mousePressEvent(QMouseEvent *event) 
{
    update();
}
void Test3D::mouseMoveEvent(QMouseEvent *event) 
{}
void Test3D::keyPressEvent(QKeyEvent *event) 
{
    switch (event->key())
    {
    case (Qt::Key_1) :
    {
        //m_cubeMaterial->unsetUniform("ml_matrix", m_UnSetUniforms[0]);
        m_UnSetUniforms[0] = !m_UnSetUniforms[0];
        break;
    }

    case (Qt::Key_2) :
    {
        ///m_sphereMaterial->unsetUniform("ml_matrix", m_UnSetUniforms[1]);
        m_UnSetUniforms[1] = !m_UnSetUniforms[1];
        break;
    }
    }
    update();
}