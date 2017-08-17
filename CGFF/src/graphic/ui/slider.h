#ifndef SLIDER_H
#define SLIDER_H

#include "widget.h"

namespace CGFF {
    namespace UI {

	class Slider : public Widget
	{
	public:
		using ValueChangedCallback = std::function<void(float)>;
	private:
		enum class SliderState
		{
			UNPRESSED, PRESSED, PRESSEDHEAD
		};
	private:
		QRect m_headBounds;
		float m_value;
		float m_headOffset;
		SliderState m_state;
		ValueChangedCallback m_callback;
		bool m_vertical;
	public:
		Slider(const QRect& bounds, bool vertical = false);
		Slider(const QRect& bounds, float value = 0.0f, const ValueChangedCallback& callback = &Slider::noCallback, bool vertical = false);
        virtual ~Slider() {};

		bool onMousePressed(QMouseEvent* e) override;
		bool onMouseReleased(QMouseEvent* e) override;
		bool onMouseMoved(QMouseEvent* e) override;

		void update() override;
		void render(QSharedPointer<Renderer2D>& renderer) override;

		inline void setCallback(const ValueChangedCallback& callback) { m_callback = callback; }
		inline const ValueChangedCallback& getCallback() const { return m_callback; }

		inline float getValue() const { return m_value; }
		void setValue(float value);
	private:
		static void noCallback(float) {}
	};

} } 

#endif