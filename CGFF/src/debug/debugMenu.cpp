#include "debugMenu.h"

namespace CGFF {

    DebugMenu* DebugMenu::s_instance = nullptr;

    DebugMenu::DebugMenu()
        : m_visible(false)
    {

    }

    void DebugMenu::init()
    {
        s_instance = new DebugMenu();
    }


    void DebugMenu::add()
    {

    }

    bool DebugMenu::isVisible()
    {
        return s_instance->m_visible;
    }

    void DebugMenu::setVisible(bool visible)
    {
        s_instance->m_visible = visible;
    }

}