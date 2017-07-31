#include "debugMenuItem.h"
#include "debugMenu.h"

namespace CGFF {

    DebugMenuItem::DebugMenuItem(QSharedPointer<IAction> action, const QRect& bounds)
        : Button(action->toString(), bounds, [action]() { action->onAction(); }), m_action(action)
    {
    }

    void DebugMenuItem::update()
    {
        m_label = m_action->toString();       
        m_font.setPixelSize(DebugMenu::get()->getSettings().fontPixelSize);
    }

}