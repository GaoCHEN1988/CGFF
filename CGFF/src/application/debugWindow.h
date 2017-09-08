#ifndef CGFF_DEBUG_WINDOW_H
#define CGFF_DEBUG_WINDOW_H

#include "baseWindow.h"
#include <QTime>

namespace CGFF {


	class DebugWindow : public BaseWindow 
	{
	public:

		DebugWindow(QWidget * parent, CGFF::RenderAPI api = CGFF::RenderAPI::OPENGL);
		virtual ~DebugWindow();

		inline static DebugWindow* getApplication() { return m_instance; }
		void initialize() override;

	private:
		static DebugWindow * m_instance;
	};
}

#endif