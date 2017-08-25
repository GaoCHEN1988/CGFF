#include "debugMenu.h"
#include "debugMenuAction.h"

#include <QPainter>

namespace CGFF {

    DebugMenu * DebugMenu::s_instance = nullptr;

    DebugMenu::DebugMenu()
        : m_visible(false)
        , m_padding(45.0f)
        , m_fontSize(24.0f)
    {
        s_instance = this;
        m_settings.padding = 50.0f;
        m_settings.fontPixelSize = 20.0f;

        add("Padding", &m_settings.padding, 20.0f, 80.0f);
        add("Font Size", &m_settings.fontPixelSize, 8.0f, 50.0f);

        m_sliders.resize(4);
        m_panel = QSharedPointer<UI::Panel>(new UI::Panel());
    }

    void DebugMenu::add(QString name)
    {
        s_instance->m_actionList.append(QSharedPointer<EmptyAction>(new EmptyAction(name)));
    }

	void DebugMenu::add(const QString& name, bool* value)
	{
		s_instance->m_actionList.append(QSharedPointer<BooleanAction>(new BooleanAction(name, [value]() { return *value; }, [value](bool v) { *value = v; })));
	}

    void DebugMenu::add(const QString& name, float* value)
    {
        add(name, value, 0.0f, 100.0f);
    }

    void DebugMenu::add(const QString& name, float* value, float minimum, float maximum)
    {
        s_instance->m_actionList.append(QSharedPointer<FloatAction>(
			new FloatAction(name, [value]() { return *value; }, [value](float v) { *value = v; }, minimum, maximum)));
    }

	void DebugMenu::add(const QString& name, QVector2D* value, float minimum, float maximum)
	{
		s_instance->m_actionList.append(QSharedPointer<Vec2Action>(
			new Vec2Action(name, [value]() { return *value; }, 
				[value](QVector2D v) { *value = v; }, 
				QVector2D(minimum, minimum), 
				QVector2D(maximum, maximum))));
	}

	void DebugMenu::add(const QString& name, QVector3D* value, float minimum, float maximum)
	{
		s_instance->m_actionList.push_back(QSharedPointer<Vec3Action>(
			new Vec3Action(name, [value]() { return *value; }, 
				[value](QVector3D v) { *value = v; }, 
				QVector3D(minimum, minimum, minimum), 
				QVector3D(maximum, maximum, maximum))));
	}

	void DebugMenu::add(const QString& name, QVector4D* value, float minimum, float maximum)
	{
		s_instance->m_actionList.push_back(QSharedPointer<Vec4Action>(
			new Vec4Action(name, [value]() { return *value; }, 
				[value](QVector4D v) { *value = v; }, 
				QVector4D(minimum, minimum, minimum, minimum),
				QVector4D(maximum, maximum, maximum, maximum))));
	}

	void DebugMenu::remove(const QString& name)
	{
		auto& actions = s_instance->m_actionList;
		for (uint i = 0; i < actions.size(); i++)
		{
			if (actions[i]->name == name)
			{
				actions.remove(i);
				break;
			}
		}
	}

    DebugMenu* DebugMenu::get()
    {
        return s_instance;
    }

    DebugMenuSettings& DebugMenu::getSettings()
    {
        return s_instance->m_settings;
    }

    bool DebugMenu::isVisible()
    {
        return s_instance->m_visible;
    }

    void DebugMenu::setVisible(bool visible)
    {
        s_instance->m_visible = visible;
        if (visible)
            s_instance->onActivate();
        else
            s_instance->onDeactivate();
    }

    void DebugMenu::render(QSharedPointer<Renderer2D>& renderer)
    {
        m_panel->render(renderer);
    }

    void DebugMenu::editValues(const QString& name, float* values, uint count, const UI::Slider::ValueChangedCallback* callbacks)
    {
        //m_slider->setCallback(callback);
        //m_slider->setActive(true);
        //m_slider->setValue(value);

		for (uint i = 0; i < 4; i++)
		{
			m_sliders[i]->setActive(false);
			if (i < count)
			{
				m_sliders[i]->setCallback(callbacks[i]);
				m_sliders[i]->setActive(m_lastEditedName != name);
				m_sliders[i]->setValue(values[i]);
			}
		}
		m_lastEditedName = m_lastEditedName != name ? name : "";
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

		for (uint i = 0; i < 4; i++)
		{
			m_sliders[i] = QSharedPointer<UI::Slider>(new UI::Slider(QRect((int)width + i * 40, 10, 40, 400), true));
			m_panel->add(m_sliders[i])->setActive(false);
		}

        //m_slider = QSharedPointer<UI::Slider>(new UI::Slider(QRect(width, 10, 40, 600), true));
        //m_panel->add(m_slider)->setActive(false);
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

	void DebugMenu::closeEvent(QEvent *event)
	{
		m_panel->closeEvent(event);
	}
}