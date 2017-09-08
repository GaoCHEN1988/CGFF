#ifndef CGFF_DEBUG_MENU_ITEM_H
#define CGFF_DEBUG_MENU_ITEM_H

//#include "debugMenuAction.h"
#include "graphic/ui/button.h"

namespace CGFF {

	struct IAction;

    class DebugMenuItem : public UI::Button
    {
    public:
		DebugMenuItem(QSharedPointer<IAction> action, const QRect& bounds, UI::Widget * parent);

        void update() override;

	protected:
        QSharedPointer<IAction> m_action;
    };

}

#endif
