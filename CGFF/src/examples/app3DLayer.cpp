#include "app3DLayer.h"

namespace CGFF
{
	App3DLayer::App3DLayer(QSize size, QWidget *parent) 
		: Layer3D(QSharedPointer<Scene>(new Scene(size))
			, QSharedPointer<ForwardRenderer>(new ForwardRenderer(size))
			, parent)
		, m_camera(nullptr)
		, m_entities()
		, m_lights()
		, m_skyboxMaterial(nullptr)
	{
	}

	App3DLayer::~App3DLayer()
	{
	}


	void App3DLayer::init()
	{

	}

	void App3DLayer::render(QSharedPointer<Renderer3D>& renderer)
	{
		// Remove the translation part for skybox
        if (m_skyboxMaterial)
        {
            QMatrix4x4 vm = m_scene->getCamera()->getViewMatrix();
            m_skyboxMaterial->setUniform("u_ViewMatrix", QMatrix4x4(QMatrix3x3(vm.toGenericMatrix<3, 3>())));
        }
	}

	void App3DLayer::resizeEvent(QResizeEvent *event)
	{
	}
	void App3DLayer::mousePressEvent(QMouseEvent *event)
	{

	}
	void App3DLayer::mouseMoveEvent(QMouseEvent *event)
	{
	}
	void App3DLayer::mouseReleaseEvent(QMouseEvent *event)
	{
	}
	void App3DLayer::keyPressEvent(QKeyEvent *event)
	{
	}
	void App3DLayer::closeEvent(QCloseEvent *event)
	{
	}

	void App3DLayer::loadFromResource()
	{
	}
}