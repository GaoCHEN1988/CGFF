#ifndef QTUI_LIGHT_VIEW_H
#define QTUI_LIGHT_VIEW_H

#include "baseView.h"
#include <QLabel>
#include <QDoubleSpinBox>

namespace QTUI {

	class LightView : public BaseView
	{
		Q_OBJECT

	public:

		LightView(QWidget *parent = Q_NULLPTR);
		virtual ~LightView() {};

		void init();
	};
}

#endif
