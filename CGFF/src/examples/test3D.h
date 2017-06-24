#ifndef TEST_3D_H
#define TEST_3D_H

#include "utils/qtopengl.h"
#include "graphic/meshFactory.h"
#include "graphic/layer/layer3D.h"
#include "graphic/model.h"
#include <QTime>
#include <QOpenGLWidget>

class Test3D : public QOpenGLWidget
{
    Q_OBJECT

public:

    Test3D(QWidget *parent = 0);
    ~Test3D() {};

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    QSharedPointer<QOpenGLShaderProgram> m_shader;
    //QSharedPointer<CGFF::Mesh> m_cube;
    QSharedPointer<CGFF::Material> m_material;
    QSharedPointer<CGFF::MaterialInstance> m_cubeMaterial;
    QSharedPointer<CGFF::MaterialInstance> m_sphereMaterial;
    CGFF::MeshFactory::Cube m_cube;
    QSharedPointer<CGFF::Model> m_model_cube;
    QSharedPointer<CGFF::Model> m_model_sphere;
    QSharedPointer<CGFF::Layer3D> m_layer;
    QMatrix4x4 m_pr_matrix;
    QMatrix4x4 m_vw_matrix;
    QMatrix4x4 m_ml_matrix;
    float m_Rotation;
    bool m_UnSetUniforms[2];

};

#endif
