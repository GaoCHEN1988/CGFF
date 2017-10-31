#include "app3DLayer.h"
#include "resource/resourceManager.h"
#include "graphic/shader/shaderFactory.h"

namespace CGFF
{
    AppType testType;

    App3DLayer::App3DLayer(QSize size, QTUI::ResourceModel * model, QWidget *parent)
        : Layer3D(QSharedPointer<Scene>(new Scene(size))
            , QSharedPointer<ForwardRenderer>(new ForwardRenderer(size))
            , parent)
        , m_shadowMapping(nullptr)
        , m_pointShadows(nullptr)
        , m_normalMapping(nullptr)
        , m_parallaxMapping(nullptr)
        , m_model(model)
    {
    }

    App3DLayer::~App3DLayer()
    {
    }


    void App3DLayer::init()
    {
        m_model->onAddScene(m_scene->getName());

        testType = AppType::pbr;

        switch (testType)
        {
        case AppType::bloom:
        {
            break;
        }
        case AppType::deferredShading:
        {
            setRenderer(QSharedPointer<DeferredRenderer>(new DeferredRenderer(m_scene->getSize())));
            m_deferredShading = QSharedPointer<LearnGL::DeferredShading>(new LearnGL::DeferredShading(m_scene));
            m_deferredShading->init();

            break;
        }
        case AppType::hdr:
        {
            m_hdr = QSharedPointer<LearnGL::HDR>(new LearnGL::HDR(m_scene));
            m_hdr->init();

            break;
        }
        case AppType::normalMapping:
        {
            m_normalMapping = QSharedPointer<LearnGL::NormalMapping>(new LearnGL::NormalMapping(m_scene));
            m_normalMapping->init();

            break;
        }
        case AppType::parallaxMapping:
        {
            m_parallaxMapping = QSharedPointer<LearnGL::ParallaxMapping>(new LearnGL::ParallaxMapping(m_scene));
            m_parallaxMapping->init();
            break;
        }
        case AppType::pbr:
        {
            m_pbr = QSharedPointer<LearnGL::PBR>(new LearnGL::PBR(m_scene));
            m_pbr->init();
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
            setRenderer(QSharedPointer<DeferredRenderer>(new DeferredRenderer(m_scene->getSize())));
            m_ssao = QSharedPointer<LearnGL::SSAO>(new LearnGL::SSAO(m_scene));
            m_ssao->init();
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
            m_deferredShading->render();
            break;
        }
        case AppType::hdr:
        {
            m_hdr->render();
            break;
        }
        case AppType::normalMapping:
        {
            m_normalMapping->render();
            break;
        }
        case AppType::parallaxMapping:
        {
            m_parallaxMapping->render();
            break;
        }
        case AppType::pbr:
        {
            m_pbr->render();
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
            m_ssao->render();
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

    void App3DLayer::keyPressEvent(QKeyEvent *event)
    {
        switch (event->key())
        {
        case (Qt::Key_1) :
        {
            Renderer::setRenderTarget(CGFF::Render3DTarget::SCREEN);
            break;
        }

        case (Qt::Key_2) :
        {
            Renderer::setRenderTarget(CGFF::Render3DTarget::BUFFER);
            break;
        }
        }
    }

    void App3DLayer::closeEvent(QCloseEvent *event)
    {
    }
}