#ifndef QTUI_MATERIAL_VIEW_H
#define QTUI_MATERIAL_VIEW_H

#include "baseView.h"
#include <QLabel>
#include <QDoubleSpinBox>

namespace QTUI {

	class MaterialView : public BaseView
	{
		Q_OBJECT

	public:

		MaterialView(QWidget *parent = Q_NULLPTR);
		virtual ~MaterialView() {};

		void init();

	private:
	};
}

#endif