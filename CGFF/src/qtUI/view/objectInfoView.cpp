#include "objectInfoView.h"
#include <QGridLayout>

namespace QTUI {

	ObjectInfoView::ObjectInfoView(QWidget *parent)
		: QWidget(parent)
		, m_position_groupBox(nullptr)
		, m_x_label(nullptr)
		, m_y_label(nullptr)
		, m_z_label(nullptr)
		, m_x_spin_box(nullptr)
		, m_y_spin_box(nullptr)
		, m_z_spin_box(nullptr)
		, m_object_name(nullptr)
	{
		init();
	}

	void ObjectInfoView::init()
	{
		QGridLayout * layout = new QGridLayout(this);

		m_position_groupBox = new QGroupBox("Position", this);

		QGridLayout * group_layout = new QGridLayout(m_position_groupBox);

		m_x_label = new QLabel("X: ", m_position_groupBox);
		group_layout->addWidget(m_x_label, 0, 0, 1, 1);

		m_y_label = new QLabel("Y: ", m_position_groupBox);
		group_layout->addWidget(m_y_label, 1, 0, 1, 1);

		m_z_label = new QLabel("Z: ", m_position_groupBox);
		group_layout->addWidget(m_z_label, 2, 0, 1, 1);

		m_x_spin_box = new QSpinBox(m_position_groupBox);
		m_x_spin_box->setValue(0);
		group_layout->addWidget(m_x_spin_box, 0, 1, 1, 1);

		m_y_spin_box = new QSpinBox(m_position_groupBox);
		m_y_spin_box->setValue(0);
		group_layout->addWidget(m_y_spin_box, 1, 1, 1, 1);

		m_z_spin_box = new QSpinBox(m_position_groupBox);
		m_z_spin_box->setValue(0);
		group_layout->addWidget(m_z_spin_box, 2, 1, 1, 1);

		m_object_name = new QLabel("Object Name ", this);

		layout->addWidget(m_object_name, 0, 0);
		layout->addWidget(m_position_groupBox, 1, 0);

		layout->setRowStretch(0, 1);
		layout->setRowStretch(1, 4);
	}
}