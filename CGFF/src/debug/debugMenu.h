#ifndef DEBUG_MENU_H
#define DEBUG_MENU_H

namespace CGFF {

    class DebugMenu
    {
    private:
        DebugMenu();

    private:
        bool m_visible;
    public:
        static void init();
        static void add();

        static bool isVisible();
        static void setVisible(bool visible);
        
    private:
        static DebugMenu * s_instance;

    };
}
#endif