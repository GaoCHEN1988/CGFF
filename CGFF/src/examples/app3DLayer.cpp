#include "app3DLayer.h"
#include "resource/resourceManager.h"
#include "graphic/shader/shaderFactory.h"

namespace CGFF
{
    AppType testType;

    App3DLayer::App3DLayer(QSize size, QWidget *parent)
        : Layer3D(QSharedPointer<Scene>(new Scene(size))
            , QSharedPointer<ForwardRenderer>(new ForwardRenderer(size))
            , parent)
        , m_shadowMapping(nullptr)
        , m_pointShadows(nullptr)
    {
    }

    App3DLayer::~App3DLayer()
    {
    }


    void App3DLayer::init()
    {
        testType = AppType::pointShadows;

        switch (testType)
        {
        case AppType::bloom:
        {
            break;
        }
        case AppType::deferredShading:
        {
            break;
        }
        case AppType::hdr:
        {
            break;
        }
        case AppType::normalMapping:
        {
            break;
        }
        case AppType::parallaxMapping:
        {
            break;
        }
        case AppType::pbr:
        {
            break;
        }
        case AppType::pointShadows:
        {
            m_pointShadows = QSharedPointer<LearnGL::PointShadows>(new LearnGL::PointShadows(m_scene));
            m_pointShadows->init();
            break;
        }
        case AppType::shadowMappingDepth:
        {
            m_shadowMapping = QSharedPointer<LearnGL::ShadowMappingDepth>(new LearnGL::ShadowMappingDepth(m_scene));
            m_shadowMapping->init();

            break;
        }
        case AppType::ssao:
        {
            break;
        }
        }
    }

    void App3DLayer::render(QSharedPointer<Renderer3D>& renderer)
    {
        switch (testType)
        {
        case AppType::bloom:
        {
            break;
        }
        case AppType::deferredShading:
        {
            break;
        }
        case AppType::hdr:
        {
            break;
        }
        case AppType::normalMapping:
        {
            break;
        }
        case AppType::parallaxMapping:
        {
            break;
        }
        case AppType::pbr:
        {
            break;
        }
        case AppType::pointShadows:
        {
            m_pointShadows->render();

            break;
        }
        case AppType::shadowMappingDepth:
        {
            m_shadowMapping->render();

            break;
        }
        case AppType::ssao:
        {
            break;
        }
        }
        
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