#ifndef CGFF_APP_WINDOW_H
#define CGFF_APP_WINDOW_H

#include "baseWindow.h"
#include <QTime>

namespace CGFF {

	class AppWindow : public BaseWindow
	{
	public:

		AppWindow(QWidget * parent, CGFF::RenderAPI api = CGFF::RenderAPI::OPENGL);
		virtual ~AppWindow();

		void initialize() override;

	};
}

#endif
