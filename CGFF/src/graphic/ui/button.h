#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

namespace CGFF { namespace UI { 

	class Button : public Widget
	{
	public:
		using ActionHandler = std::function<void()>;
	private:
		enum class ButtonState
		{
			UNPRESSED, PRESSED
		};

	public:
		Button(const QString& label, const QRect& bounds, UI::Widget * parent, const ActionHandler& handler = &Button::noAction);
        virtual ~Button();

		bool onMousePressed(QMouseEvent* e) override;
		bool onMouseReleased(QMouseEvent* e) override;
		bool onMouseMoved(QMouseEvent* e) override;

		virtual void onAction();
		virtual void update() override;
		virtual void render(QSharedPointer<Renderer2D>& renderer) override;

		inline void setLabel(const QString& label) { m_label = label; }
		inline const QString& GetLabel() const { return m_label; }

		inline void setFont(QFont font) { m_font = font; }
		inline const QFont GetFont() const { return m_font; }

		inline void setAction(const ActionHandler& action) { m_actionHandler = action; }
	private:
		static void noAction() {}

    protected:
        QString m_label;
        ButtonState m_state;
        ActionHandler m_actionHandler;
        QFont m_font;
		UI::Widget* m_parent;
	};


} }

#endif