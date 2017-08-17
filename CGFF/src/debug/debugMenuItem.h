#ifndef DEBUG_MENU_ITEM_H
#define DEBUG_MENU_ITEM_H

//#include "debugMenuAction.h"
#include "graphic/ui/button.h"

namespace CGFF {

	struct IAction;

    class DebugMenuItem : public UI::Button
    {
    public:
        DebugMenuItem(QSharedPointer<IAction> action, const QRect& bounds);

        void update() override;

    private:
        QSharedPointer<IAction> m_action;
    };

}

#endif
