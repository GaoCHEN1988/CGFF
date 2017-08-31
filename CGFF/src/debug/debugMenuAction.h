#ifndef CGFF_DEBUG_MENU_ACTION_H
#define CGFF_DEBUG_MENU_ACTION_H

#include <QString>
#include <QSharedPointer>
#include "common.h"

namespace CGFF {

    struct IAction
    {
		enum class Type
		{
			NONE = 0, EMPTY, PATH, BOOLEAN, VALUE, VEC2, VEC3, VEC4
		};

        QString name;
		Type type;
        virtual void onAction() = 0;
        virtual QString toString() = 0;
    };

	typedef QVector<QSharedPointer<IAction>> ActionList;

    struct EmptyAction : public IAction
    {
        EmptyAction(const QString& name) 
		{ 
			this->name = name; 
			this->type = Type::EMPTY;
		}
        void onAction() override {}
        QString toString() override { return name; }
    };

	struct PathAction : public IAction, public QEnableSharedFromThis<PathAction>
	{
		ActionList actionList;
		QSharedPointer<PathAction> parent;

		PathAction(const QString& name, QSharedPointer<PathAction> parent)
		{
			this->name = name;
			this->parent = parent;
			type = Type::PATH;
		}

		void onAction() override
		{
			DebugMenu::setPath(sharedFromThis());
		}

		QString toString() override
		{
			return name + "  >";
		}

		bool containsAction(const QString& name)
		{
			for (QSharedPointer<IAction> action : actionList)
			{
				if (action->name == name)
					return true;
			}
			return false;
		}

		QSharedPointer<PathAction> findPath(const QString& name)
		{
			for (QSharedPointer<IAction> action : actionList)
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

		bool DeleteChild(QSharedPointer<PathAction> child)
		{
			for (uint i = 0; i < actionList.size(); i++)
			{
				if (actionList[i] == child)
				{
					actionList.remove(i);
					return true;
				}
			}
			return false;
		}
	};

	struct BackAction : public IAction
	{
		QSharedPointer<PathAction> destination;

		BackAction(QSharedPointer<PathAction> destination)
		{
			this->name = "..  ";
			this->destination = destination;
			type = Type::PATH;
		}

		void onAction() override
		{
			DebugMenu::setPath(destination);
		}

		QString toString() override
		{
			return name;
		}
	};

	struct CustomAction : public IAction
	{
	private:
		std::function<void()> m_function;
	public:
		CustomAction(const QString& name, const std::function<void()>& function)
			: m_function(function)
		{
			this->name = name;
		}

		void onAction() override
		{
			m_function();
		}

		QString toString() override
		{
			return name;
		}
	};

	struct BooleanAction : public IAction
	{
		using Getter = std::function<bool()>;
		using Setter = std::function<void(bool)>;
	private:
		Getter m_getter;
		Setter m_setter;
	public:
		BooleanAction(const QString& name, const Getter& getter, const Setter& setter)
			: m_getter(getter), m_setter(setter) {
			this->name = name;
		}

		void onAction() override
		{
			m_setter(!m_getter());
		}

		QString toString() override
		{
			return name + "             " + (m_getter() ? "v" : "x");
		}
	};

    template<typename T>
    struct ValueAction : public IAction
    {
        using Getter = std::function<T()>;
        using Setter = std::function<void(T)>;
    private:
        Getter m_getter;
        Setter m_setter;
        T m_min, m_max;
    public:
        ValueAction(const QString& name, const Getter& getter, const Setter& setter, T minValue, T maxValue)
            : m_getter(getter)
            , m_setter(setter)
            , m_min(minValue)
            , m_max(maxValue) 
        {
            this->name = name;
        }

        void onAction() override
        {
            //DebugMenu::get()->editValue((m_getter() - m_min) / (m_max - m_min), CGFF_METHOD(&ValueAction::onValueChanged));
			Q_ASSERT(false);
        }

        QString toString() override
        {
            return name + " " + QString::number(m_getter());
        }
    };

	template<>
	void ValueAction<float>::onAction()
	{
		float values[1] = { (m_getter() - m_min) / (m_max - m_min) };
		UI::Slider::ValueChangedCallback callback[1] = { [&](float value) { m_setter(value * (m_max - m_min) + m_min); } };
		DebugMenu::get()->editValues(name, values, 1, callback);
	}

	template<>
	void ValueAction<QVector2D>::onAction()
	{
		float values[2] =
		{
			(m_getter().x() - m_min.x()) / (m_max.x() - m_min.x()),
			(m_getter().y() - m_min.y()) / (m_max.y() - m_min.y())
		};
		UI::Slider::ValueChangedCallback callbacks[2] =
		{
			[&](float value) { m_setter(QVector2D(value * (m_max.x() - m_min.x()) + m_min.x(), m_getter().y())); },
			[&](float value) { m_setter(QVector2D(m_getter().x(), value * (m_max.y() - m_min.y()) + m_min.y())); }
		};
		DebugMenu::get()->editValues(name, values, 2, callbacks);
	}

	template<>
	QString ValueAction<QVector2D>::toString()
	{
		return name + " " + QString::number(m_getter().x()) + ", " + QString::number(m_getter().y());
	}

	template<>
	void ValueAction<QVector3D>::onAction()
	{
		float values[3] =
		{
			(m_getter().x() - m_min.x()) / (m_max.x() - m_min.x()),
			(m_getter().y() - m_min.y()) / (m_max.y() - m_min.y()),
			(m_getter().z() - m_min.z()) / (m_max.z() - m_min.z())
		};
		UI::Slider::ValueChangedCallback callbacks[3] =
		{
			[&](float value) { m_setter(QVector3D(value * (m_max.x() - m_min.x()) + m_min.x(), m_getter().y(), m_getter().z())); },
			[&](float value) { m_setter(QVector3D(m_getter().x(), value * (m_max.y() - m_min.y()) + m_min.y(), m_getter().z())); },
			[&](float value) { m_setter(QVector3D(m_getter().x(), m_getter().y(), value * (m_max.z() - m_min.z()) + m_min.z())); }
		};
		DebugMenu::get()->editValues(name, values, 3, callbacks);
	}

	template<>
	QString ValueAction<QVector3D>::toString()
	{
		return name + " " + QString::number(m_getter().x()) + ", " + QString::number(m_getter().y()) + ", " + QString::number(m_getter().z());
	}

	template<>
	void ValueAction<QVector4D>::onAction()
	{
		float values[4] =
		{
			(m_getter().x() - m_min.x()) / (m_max.x() - m_min.x()),
			(m_getter().y() - m_min.y()) / (m_max.y() - m_min.y()),
			(m_getter().z() - m_min.z()) / (m_max.z() - m_min.z()),
			(m_getter().w() - m_min.w()) / (m_max.w() - m_min.w())
		};
		UI::Slider::ValueChangedCallback callbacks[4] =
		{
			[&](float value) { m_setter(QVector4D(value * (m_max.x() - m_min.x()) + m_min.x(), m_getter().y(), m_getter().z(), m_getter().w())); },
			[&](float value) { m_setter(QVector4D(m_getter().x(), value * (m_max.y() - m_min.y()) + m_min.y(), m_getter().z(), m_getter().w())); },
			[&](float value) { m_setter(QVector4D(m_getter().x(), m_getter().y(), value * (m_max.z() - m_min.z()) + m_min.z(), m_getter().w())); },
			[&](float value) { m_setter(QVector4D(m_getter().x(), m_getter().y(), m_getter().z(), value * (m_max.w() - m_min.w()) + m_min.w())); }
		};
		DebugMenu::get()->editValues(name, values, 4, callbacks);
	}

	template<>
	QString ValueAction<QVector4D>::toString()
	{
		return name + " " + QString::number(m_getter().x()) + ", " + QString::number(m_getter().y()) + ", " + QString::number(m_getter().z()) + ", " + QString::number(m_getter().w());
	}

    typedef ValueAction<int> IntAction;
    typedef ValueAction<float> FloatAction;

	typedef ValueAction<QVector2D> Vec2Action;
	typedef ValueAction<QVector3D> Vec3Action;
	typedef ValueAction<QVector4D> Vec4Action;

}

#endif