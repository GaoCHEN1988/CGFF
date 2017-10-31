#ifndef CGFF_DEBUG_LAYER_3D_H
#define CGFF_DEBUG_LAYER_3D_H

#include "graphic/layer/layer3D.h"
#include "qtUI/model/resourceModel.h"

namespace CGFF {

	class DebugLayer3D : public Layer3D
	{
	public:
		DebugLayer3D(const QSize& size, QTUI::ResourceModel * model, QWidget *parent = Q_NULLPTR);

		void init() override;
		void render(QSharedPointer<Renderer3D>& renderer) override;
		void tick() override;
		void closeEvent(QCloseEvent *event) override;

		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;

	private:
		QSharedPointer<CGFF::Camera> m_mayaCamera;
		QSharedPointer<Shader> m_debugShader;

		QSharedPointer<CGFF::Entity> m_lineX;
		QSharedPointer<CGFF::Entity> m_lineY;
		QSharedPointer<CGFF::Entity> m_lineZ;

		QSharedPointer<MaterialInstance> m_debugMaterial;

        QTUI::ResourceModel * m_model;
	};

}
#endif