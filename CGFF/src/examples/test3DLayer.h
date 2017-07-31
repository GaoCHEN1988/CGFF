#ifndef TEST_3D_LAYER_H
#define TEST_3D_LAYER_H

#include "graphic/layer/layer3D.h"
#include "graphic/meshFactory.h"
#include "graphic/model.h"
#include "entity/entity.h"

namespace CGFF {
    class Test3DLayer : public Layer3D
    {
    public:
        Test3DLayer();
        virtual~Test3DLayer() {};

        void init() override;
        void render() override;

        void resize(int width, int height) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:
        QSharedPointer<QOpenGLShaderProgram> m_shader;
        QSharedPointer<CGFF::Material> m_material;
        QSharedPointer<CGFF::Entity> m_cube;
        QSharedPointer<CGFF::Entity> m_sphere;
        QSharedPointer<CGFF::Entity> m_plane;
        CGFF::MeshFactory::Plane m_plane_mesh;
        QSharedPointer<CGFF::Model> m_model_cube;
        QSharedPointer<CGFF::Model> m_model_sphere;

        QMatrix4x4 m_vw_matrix;
        QMatrix4x4 m_ml_matrix;
        float m_rotation;
        float m_transform;
    };
}

#endif
