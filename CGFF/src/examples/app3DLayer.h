#ifndef APP_3D_LAYER_H
#define APP_3D_LAYER_H

#include "graphic/layer/layer3D.h"
#include "examples/learnOpengl/learnGL.h"

namespace CGFF {

    enum class AppType
    {
        bloom,
        deferredShading,
        hdr,
        normalMapping,
        parallaxMapping,
        pbr,
        pointShadows,
        shadowMappingDepth,
        ssao
    };

	class App3DLayer : public Layer3D
	{
	public:
		App3DLayer(QSize size, QWidget *parent = Q_NULLPTR);
		virtual ~App3DLayer();

		void init() override;
		void render(QSharedPointer<Renderer3D>& renderer) override;

		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

	private:
        QSharedPointer<LearnGL::ShadowMappingDepth> m_shadowMapping;
        QSharedPointer<LearnGL::PointShadows> m_pointShadows;
        QSharedPointer<LearnGL::NormalMapping> m_normalMapping;
        QSharedPointer<LearnGL::ParallaxMapping> m_parallaxMapping;
        QSharedPointer<LearnGL::HDR> m_hdr;
        QSharedPointer<LearnGL::DeferredShading> m_deferredShading;
	};
}

#endif