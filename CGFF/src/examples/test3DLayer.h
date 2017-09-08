#ifndef TEST_3D_LAYER_H
#define TEST_3D_LAYER_H

#include "graphic/api/framebufferDepth.h"
#include "graphic/api/textureDepth.h"
#include "graphic/layer/layer3D.h"
#include "graphic/meshFactory.h"
#include "graphic/model.h"
#include "entity/entity.h"
#include "graphic/pbrMaterial.h"
#include "graphic/shader/shaderManager.h"

namespace CGFF {
    class Test3DLayer : public Layer3D
    {
    public:
        Test3DLayer(QSize size, QWidget *parent = Q_NULLPTR);
        virtual ~Test3DLayer();

        void init() override;
		void render(QSharedPointer<Renderer3D>& renderer) override;

        //void resize(int width, int height) override;
		void resizeEvent(QResizeEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
		//void closeEvent(QEvent *event) override;

    private:

        QSharedPointer<CGFF::Camera> m_mayaCamera;
        QSharedPointer<CGFF::Camera> m_FPSCamera;

		QVector<QSharedPointer<CGFF::Entity>> m_Spheres;
		QSharedPointer<CGFF::Entity> m_plane;
		QSharedPointer<CGFF::Entity> m_dagger;
		QSharedPointer<CGFF::Entity> m_cube;
		QSharedPointer<CGFF::PBRMaterial> m_daggerMaterial;
		QSharedPointer<CGFF::PBRMaterial> m_planeMaterial;
		QSharedPointer<CGFF::MaterialInstance> m_skyboxMaterial;
		QSharedPointer<CGFF::Light> m_light;

		float m_rotation;

		QVector<QSharedPointer<CGFF::MaterialInstance>> m_materials;
    };
}

#endif
