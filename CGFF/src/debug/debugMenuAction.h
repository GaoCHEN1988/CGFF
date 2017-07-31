#ifndef DEBUG_MENU_ACTION_H
#define DEBUG_MENU_ACTION_H

#include <QString>
#include "common.h"

namespace CGFF {

    struct IAction
    {
        QString name;
        virtual void onAction() = 0;
        virtual QString toString() = 0;
    };

    struct EmptyAction : public IAction
    {
        EmptyAction(const QString& name) { this->name = name; }
        void onAction() override {}
        QString toString() override { return name; }
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
            DebugMenu::get()->editValue((m_getter() - m_min) / (m_max - m_min), CGFF_METHOD(&ValueAction::onValueChanged));
        }

        void onValueChanged(float value)
        {
            m_setter(value * (m_max - m_min) + m_min);
        }

        QString toString() override
        {
            return name + " " + QString::number(m_getter());
        }
    };

    typedef ValueAction<int> IntAction;
    typedef ValueAction<float> FloatAction;

}

#endif