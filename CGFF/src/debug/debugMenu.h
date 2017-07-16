#ifndef DEBUG_MENU_H
#define DEBUG_MENU_H

#include "graphic/renderer2d.h"

namespace CGFF {

    struct DebugMenuItem
    {
        QString name;
    };

    class DebugMenu
    {
    private:
        DebugMenu();

    public:
        static void init()
        {
            static DebugMenu instance;
            m_instance = &instance;
        };
        static void add(QString name);

        static bool isVisible();
        static void setVisible(bool visible);
        static void render(QSharedPointer<Renderer2D>& renderer);
        
    private:
        static DebugMenu * m_instance;
        bool m_visible;
        QVector<DebugMenuItem> m_debugMenuItems;
    };
}
#endif