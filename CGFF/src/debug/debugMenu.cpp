#include "debugMenu.h"
#include <QPainter>

namespace CGFF {

    DebugMenu * DebugMenu::m_instance = nullptr;

    DebugMenu::DebugMenu()
        : m_visible(false)
        , m_padding(45.0f)
        , m_fontSize(24.0f)
    {
        m_instance = this;
        m_settings.padding = 50.0f;
        m_settings.fontPixelSize = 20.0f;

        add("Padding", &m_settings.padding, 20.0f, 80.0f);
        add("Font Size", &m_settings.fontPixelSize, 8.0f, 50.0f);

        m_slider = nullptr;
        m_panel = QSharedPointer<UI::Panel>(new UI::Panel());
    }

    void DebugMenu::add(QString name)
    {
        m_instance->m_actionList.append(QSharedPointer<EmptyAction>(new EmptyAction(name)));
    }

    void DebugMenu::add(const QString& name, float* value)
    {
        add(name, value, 0.0f, 100.0f);
    }

    void DebugMenu::add(const QString& name, float* value, float mininmum, float maximum)
    {
        m_instance->m_actionList.append(QSharedPointer<FloatAction>(new FloatAction(name, [value]() { return *value; }, [value](float v) { *value = v; }, mininmum, maximum)));
    }

    DebugMenu* DebugMenu::get()
    {
        return m_instance;
    }

    DebugMenuSettings& DebugMenu::getSettings()
    {
        return m_instance->m_settings;
    }

    bool DebugMenu::isVisible()
    {
        return m_instance->m_visible;
    }

    void DebugMenu::setVisible(bool visible)
    {
        m_instance->m_visible = visible;
        if (visible)
            m_instance->onActivate();
        else
            m_instance->onDeactivate();
    }

    void DebugMenu::render(QSharedPointer<Renderer2D>& renderer)
    {
        m_panel->render(renderer);
    }

    void DebugMenu::editValue(float value, const UI::Slider::ValueChangedCallback& callback)
    {
        m_slider->setCallback(callback);
        m_slider->setActive(true);
        m_slider->setValue(value);
    }

    void DebugMenu::onActivate()
    {
        float width = m_settings.padding * 5;
        float height = 1.0f + m_settings.padding;
        float yOffset = 10;
        for (QSharedPointer<IAction> action : m_actionList)
        {
            float y = yOffset;
            m_panel->add(QSharedPointer<DebugMenuItem>(new DebugMenuItem(action, QRect(0.0f, y, width, height))));
            yOffset += height;
        }

        m_slider = QSharedPointer<UI::Slider>(new UI::Slider(QRect(width, 10, 40, 600), true));
        m_panel->add(m_slider)->setActive(false);
    }

    void DebugMenu::onDeactivate()
    {
        m_panel->clear();
    }

    void DebugMenu::mousePressEvent(QMouseEvent *event)
    {
        m_panel->mousePressEvent(event);
    }

    void DebugMenu::mouseMoveEvent(QMouseEvent *event)
    {
        m_panel->mouseMoveEvent(event);
    }

    void DebugMenu::mouseReleaseEvent(QMouseEvent *event)
    {
        m_panel->mouseReleaseEvent(event);
    }

    void DebugMenu::update()
    {
        m_panel->update();
    }
}