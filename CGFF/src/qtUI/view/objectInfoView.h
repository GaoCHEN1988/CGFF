#ifndef QTUI_OBJECT_INFO_VIEW_H
#define QTUI_OBJECT_INFO_VIEW_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include "baseView.h"
#include "transformView.h"

namespace QTUI {

	class ObjectInfoView : public BaseView
	{
		Q_OBJECT

	public:

		ObjectInfoView(QWidget *parent = Q_NULLPTR);
		virtual ~ObjectInfoView() {};

	private:
		void init();

	private:
		QGroupBox * m_transform_groupBox;
        QGroupBox * m_material_groupBox;
		QLabel* m_object_name_label;
		TransformView* m_transformView;
	};
}

#endif