#ifndef QTUI_OBJECT_INFO_VIEW_H
#define QTUI_OBJECT_INFO_VIEW_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

namespace QTUI {

	class ObjectInfoView : public QWidget
	{
		Q_OBJECT

	public:

		ObjectInfoView(QWidget *parent = Q_NULLPTR);
		virtual ~ObjectInfoView() {};

	private:
		void init();

	private:
		QGroupBox * m_position_groupBox;
		QLabel* m_x_label;
		QLabel* m_y_label;
		QLabel* m_z_label;
		QSpinBox* m_x_spin_box;
		QSpinBox* m_y_spin_box;
		QSpinBox* m_z_spin_box;
		QLabel* m_object_name;
	};
}

#endif