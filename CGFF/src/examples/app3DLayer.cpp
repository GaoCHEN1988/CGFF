#include "app3DLayer.h"
#include "resource/resourceManager.h"
#include "graphic/shader/shaderFactory.h"

namespace CGFF
{
	App3DLayer::App3DLayer(QSize size, QWidget *parent) 
		: Layer3D(QSharedPointer<Scene>(new Scene(size))
			, QSharedPointer<ForwardRenderer>(new ForwardRenderer(size))
			, parent)
        , m_shadowMapping(nullptr)
	{
	}

	App3DLayer::~App3DLayer()
	{
	}


	void App3DLayer::init()
	{
        m_shadowMapping = QSharedPointer<LearnGL::ShadowMappingDepth>(new LearnGL::ShadowMappingDepth(m_scene));
        m_shadowMapping->init();
	}

	void App3DLayer::render(QSharedPointer<Renderer3D>& renderer)
	{
        m_shadowMapping->render();
	}

	void App3DLayer::mousePressEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mousePressEvent(event);
	}

	void App3DLayer::mouseMoveEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mouseMoveEvent(event);
	}

	void App3DLayer::mouseReleaseEvent(QMouseEvent *event)
	{
		Layer3D::getScene()->getCamera()->mousePressEvent(event);
	}

	void App3DLayer::closeEvent(QCloseEvent *event)
	{
	}
}