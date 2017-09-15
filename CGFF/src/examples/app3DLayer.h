#ifndef APP_3D_LAYER_H
#define APP_3D_LAYER_H

#include "graphic/api/framebufferDepth.h"
#include "graphic/api/textureDepth.h"
#include "graphic/layer/layer3D.h"
#include "graphic/meshFactory.h"
#include "graphic/model.h"
#include "entity/entity.h"
#include "graphic/pbrMaterial.h"

namespace CGFF {

	class App3DLayer : public Layer3D
	{
	public:
		App3DLayer(QSize size, QWidget *parent = Q_NULLPTR);
		virtual ~App3DLayer();

		void init() override;
		void render(QSharedPointer<Renderer3D>& renderer) override;

		void resizeEvent(QResizeEvent *event) override;
		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
		void keyPressEvent(QKeyEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

	private:
		void loadFromResource();

	private:

		QSharedPointer<Camera> m_camera;
		QVector<QSharedPointer<Entity>> m_entities;
		QVector<QSharedPointer<Light>> m_lights;
		QSharedPointer<MaterialInstance> m_skyboxMaterial;
	};
}

#endif