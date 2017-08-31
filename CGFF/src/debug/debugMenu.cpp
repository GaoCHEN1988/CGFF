#include "debugMenu.h"
#include "debugMenuAction.h"

#include <QPainter>

namespace CGFF {

    DebugMenu * DebugMenu::s_instance = nullptr;

    DebugMenu::DebugMenu()
        : m_visible(false)
		, m_path(nullptr)
    {
        s_instance = this;
        m_settings.padding = 50.0f;
        m_settings.fontPixelSize = 20.0f;

        add("Debug Menu/Padding", &m_settings.padding, 20.0f, 80.0f);
        add("Debug Menu/Font Size", &m_settings.fontPixelSize, 8.0f, 50.0f);

        m_sliders.resize(4);
        m_panel = QSharedPointer<UI::Panel>(new UI::Panel());
    }

	QSharedPointer<PathAction> DebugMenu::createOrFindPaths(QStringList& paths, QSharedPointer<PathAction> action)
	{
		if (paths.empty())
			return action;

		QString name = paths.front();
		paths.erase(paths.begin());

		ActionList* actionList = action ? &action->actionList : &m_actionList;
		for (QSharedPointer<IAction> a : *actionList)
		{
			if (a->type == IAction::Type::PATH && a->name == name)
				return createOrFindPaths(paths, qSharedPointerCast<PathAction>(a));
		}

		QSharedPointer<PathAction> pathAction = QSharedPointer<PathAction>(new PathAction(name, action));
		actionList->push_back(pathAction);
		return createOrFindPaths(paths, pathAction);
	}

	void DebugMenu::refresh()
	{
		if (!m_panel || !isVisible())
			return;

		onDeactivate();
		onActivate();
	}

	void DebugMenu::add(const QString& path, QSharedPointer<IAction> action)
	{
		if (path.contains("/"))
		{
			QStringList paths = path.split("/");
			//Test
			path.split("/");
			action->name = paths.back();
			paths.pop_back();
			QSharedPointer<PathAction> pathAction = s_instance->createOrFindPaths(paths);
			Q_ASSERT(!pathAction.isNull());
			pathAction->actionList.push_back(action);
		}
		else
		{
			s_instance->m_actionList.push_back(action);
		}

		s_instance->refresh();
	}

	void DebugMenu::add(const QString& path)
	{
		add(path, QSharedPointer<EmptyAction>(new EmptyAction(path)));
	}

	void DebugMenu::add(const QString& path, const std::function<void()>& function)
	{
		add(path, QSharedPointer<CustomAction>(new CustomAction(path, function)));
	}

	void DebugMenu::add(const QString& path, bool* value)
	{
		add(path, QSharedPointer<BooleanAction>(new BooleanAction(path, [value]() { return *value; }, [value](bool v) { *value = v; })));
	}

    void DebugMenu::add(const QString& path, float* value)
    {
        add(path, value, 0.0f, 100.0f);
    }

    void DebugMenu::add(const QString& path, float* value, float minimum, float maximum)
    {
		add(path, QSharedPointer<FloatAction>(
			new FloatAction(path, [value]() { return *value; }, [value](float v) { *value = v; }, minimum, maximum)));
    }

	void DebugMenu::add(const QString& path, QVector2D* value, float minimum, float maximum)
	{
		add(path, QSharedPointer<Vec2Action>(
			new Vec2Action(path, [value]() { return *value; }, 
				[value](QVector2D v) { *value = v; }, 
				QVector2D(minimum, minimum), 
				QVector2D(maximum, maximum))));
	}

	void DebugMenu::add(const QString& path, QVector3D* value, float minimum, float maximum)
	{
		add(path, QSharedPointer<Vec3Action>(
			new Vec3Action(path, [value]() { return *value; }, 
				[value](QVector3D v) { *value = v; }, 
				QVector3D(minimum, minimum, minimum), 
				QVector3D(maximum, maximum, maximum))));
	}

	void DebugMenu::add(const QString& path, QVector4D* value, float minimum, float maximum)
	{
		add(path, QSharedPointer<Vec4Action>(
			new Vec4Action(path, [value]() { return *value; }, 
				[value](QVector4D v) { *value = v; }, 
				QVector4D(minimum, minimum, minimum, minimum),
				QVector4D(maximum, maximum, maximum, maximum))));
	}

	void DebugMenu::remove(const QString& path)
	{
		if (path.contains("/"))
		{
			QStringList paths = path.split("/");
			QString name = paths.back();
			paths.pop_back();
			QSharedPointer<PathAction> pathAction = s_instance->createOrFindPaths(paths);
			Q_ASSERT(!pathAction.isNull());
			if (pathAction->containsAction(name))
			{
				if (pathAction->actionList.size() == 1)
				{
					QSharedPointer<PathAction> parent = pathAction->parent;
					if (parent)
					{
						parent->DeleteChild(pathAction);
					}
					else
					{
						for (uint i = 0; i < s_instance->m_actionList.size(); i++)
						{
							if (s_instance->m_actionList[i] == pathAction)
							{
								s_instance->m_actionList.remove(i);
								break;
							}
						}
					}
					while (parent)
					{
						pathAction.clear();
						pathAction = pathAction->parent;
					}
				}
				else
				{
					ActionList& actionList = pathAction->actionList;
					for (uint i = 0; i < actionList.size(); i++)
					{
						if (actionList[i]->name == name)
						{
							actionList.erase(actionList.begin() + i);
							break;
						}
					}
				}
			}
		}
		else
		{
			auto& actions = s_instance->m_actionList;
			for (uint i = 0; i < actions.size(); i++)
			{
				if (actions[i]->name == path)
				{
					actions.remove(i);
					break;
				}
			}
		}

		s_instance->refresh();
	}

	QSharedPointer<PathAction> DebugMenu::findPath(const QString& name)
	{
		for (QSharedPointer<IAction> action : m_actionList)
		{
			if (action->type == IAction::Type::PATH)
			{
				QSharedPointer<PathAction> a = qSharedPointerCast<PathAction>(action);
				if (a->name == name)
					return a;
				else
					a->findPath(name);
			}
		}
		return nullptr;
	}

    DebugMenu* DebugMenu::get()
    {
        return s_instance;
    }

    DebugMenuSettings& DebugMenu::getSettings()
    {
        return s_instance->m_settings;
    }

	void DebugMenu::setPath(QSharedPointer<PathAction> path)
	{
		s_instance->m_path = path;
		s_instance->onDeactivate();
		s_instance->onActivate();
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

		ActionList* actionList = m_path ? &m_path->actionList : &m_actionList;
		if (m_path)
		{
			QSharedPointer<DebugMenuItem> item = QSharedPointer<DebugMenuItem>(
				new DebugMenuItem(QSharedPointer<BackAction>(new BackAction(m_path->parent)),
					QRect(0.0f, yOffset, width, height)));
			m_panel->add(item);
			yOffset += height;
		}

        for (QSharedPointer<IAction> action : *actionList)
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