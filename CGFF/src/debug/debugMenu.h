#ifndef DEBUG_MENU_H
#define DEBUG_MENU_H

//#include "debugMenuAction.h"
#include "graphic/renderer2d.h"
#include "graphic/ui/slider.h"
#include "graphic/ui/panel.h"
#include "debugMenuItem.h"

namespace CGFF {

	struct IAction;
    typedef QVector<QSharedPointer<IAction>> ActionList;

    struct DebugMenuSettings
    {
        float padding;
        float fontPixelSize;
    };

    class DebugMenu
    {
    private:
        DebugMenu();

    public:
        static void init()
        {
            static DebugMenu instance;
        };

        static void add(QString name);
		static void add(const QString& name, bool* value);
        static void add(const QString& name, float* value);
        static void add(const QString& name, float* value, float minimum, float maximum);
		static void add(const QString& name, QVector2D* value, float minimum = 0.0f, float maximum = 100.0f);
		static void add(const QString& name, QVector3D* value, float minimum = 0.0f, float maximum = 100.0f);
		static void add(const QString& name, QVector4D* value, float minimum = 0.0f, float maximum = 100.0f);


        static DebugMenu* get();
        static DebugMenuSettings& getSettings();

        static bool isVisible();
        static void setVisible(bool visible);
        //static void render(QSharedPointer<Renderer2D>& renderer);
        //void editValue(float value, const UI::Slider::ValueChangedCallback& callback);
		void editValues(const QString& name, float* values, uint count, const UI::Slider::ValueChangedCallback* callbacks);

        void render(QSharedPointer<Renderer2D>& renderer);
        void onActivate();
        void onDeactivate();
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void update();
    


    private:
        static DebugMenu * s_instance;
        bool m_visible;
        DebugMenuSettings m_settings;
        ActionList m_actionList;
        float m_padding, m_fontSize;

        QSharedPointer<UI::Panel> m_panel;
        QVector<QSharedPointer<UI::Slider>> m_sliders;

		QString m_lastEditedName;
    };
}
#endif