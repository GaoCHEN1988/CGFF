#include "examples/test3D.h"
#include <QKeyEvent>


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

    m_shader->bind();
    m_pr_matrix.perspective(45.0f, GLfloat(16) / GLfloat(9), 0.01f, 1000.0f);
    m_vw_matrix.translate(QVector3D(0, 0, -10.0f));
    m_ml_matrix.rotate(45.0, QVector3D(0, 1, 0));
    m_shader->setUniformValue("pr_matrix", m_pr_matrix);
    m_shader->setUniformValue("vw_matrix", m_vw_matrix);
    m_shader->setUniformValue("ml_matrix", m_ml_matrix);

    m_shader->release();

    m_material = QSharedPointer<CGFF::Material>(new CGFF::Material(m_shader));
    m_cube.load(m_shader, 5.0, QSharedPointer<CGFF::MaterialInstance>( new CGFF::MaterialInstance(m_material)));
    m_layer = QSharedPointer<CGFF::Layer3D>(new CGFF::Layer3D(
        QSharedPointer<CGFF::Scene>(new CGFF::Scene())));

    m_layer->GetScene()->add(m_cube.mesh);
}

void Test3D::paintGL() 
{
    CGFF::GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CGFF::GL->glEnable(GL_BLEND);
    CGFF::GL->glEnable(GL_DEPTH_TEST);
    CGFF::GL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //// Use our shader
    m_shader->bind(); //Equal to glUseProgram
    m_shader->setUniformValue("pr_matrix", m_pr_matrix);
    m_shader->setUniformValue("vw_matrix", m_vw_matrix);

    m_ml_matrix.rotate(m_Rotation, QVector3D(1, 1, 0));
    m_shader->setUniformValue("ml_matrix", m_ml_matrix);
    m_Rotation += 0.5f;
    m_shader->release();

    m_layer->render();

    GLenum error = CGFF::GL->glGetError();
    if (error != GL_NO_ERROR)
    {
        //To do: show error in logging system
        int error = 1;
    }
}

void Test3D::resizeGL(int width, int height) 
{

}
void Test3D::mousePressEvent(QMouseEvent *event) 
{
    update();
}
void Test3D::mouseMoveEvent(QMouseEvent *event) 
{}
void Test3D::keyPressEvent(QKeyEvent *event) 
{}