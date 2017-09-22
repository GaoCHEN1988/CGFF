#include "transformView.h"
#include <QGridLayout>

namespace QTUI {

	TransformView::TransformView(QWidget *parent)
		: BaseView(parent)

		, m_position(nullptr)
		, m_x_label(nullptr)
		, m_y_label(nullptr)
		, m_z_label(nullptr)
		, m_x_spin_box(nullptr)
		, m_y_spin_box(nullptr)
		, m_z_spin_box(nullptr)
		, m_rotation(nullptr)
		, m_x_rotation_label(nullptr)
		, m_y_rotation_label(nullptr)
		, m_z_rotation_label(nullptr)
		, m_x_rotation_spin_box(nullptr)
		, m_y_rotation_spin_box(nullptr)
		, m_z_rotation_spin_box(nullptr)
		, m_scale(nullptr)
		, m_x_scale_label(nullptr)
		, m_y_scale_label(nullptr)
		, m_z_scale_label(nullptr)
		, m_x_scale_spin_box(nullptr)
		, m_y_scale_spin_box(nullptr)
		, m_z_scale_spin_box(nullptr)
	{
		init();
	}

	void TransformView::init()
	{
		QGridLayout * layout = new QGridLayout(this);

		//Position
		m_position = new QLabel("position: ", this);
		layout->addWidget(m_position, 0, 0, 1, 2);

		m_x_label = new QLabel("x", this);
		layout->addWidget(m_x_label, 0, 3, 1, 1);

		m_x_spin_box = new QDoubleSpinBox(this);
		m_x_spin_box->setValue(0);
		m_x_spin_box->setMinimum(-100.0);
		layout->addWidget(m_x_spin_box, 0, 4, 1, 2);

		m_y_label = new QLabel("y", this);
		layout->addWidget(m_y_label, 0, 6, 1, 1);

		m_y_spin_box = new QDoubleSpinBox(this);
		m_y_spin_box->setValue(0);
		m_y_spin_box->setMinimum(-100.0);
		layout->addWidget(m_y_spin_box, 0, 7, 1, 2);

		m_z_label = new QLabel("z", this);
		layout->addWidget(m_z_label, 0, 9, 1, 1);

		m_z_spin_box = new QDoubleSpinBox(this);
		m_z_spin_box->setValue(0);
		m_z_spin_box->setMinimum(-100.0);
		layout->addWidget(m_z_spin_box, 0, 10, 1, 2);

		//Rotation
		m_rotation = new QLabel("rotatiom: ", this);
		layout->addWidget(m_rotation, 1, 0, 1, 2);

		m_x_rotation_label = new QLabel("x", this);
		layout->addWidget(m_x_rotation_label, 1, 3, 1, 1);

		m_x_rotation_spin_box = new QDoubleSpinBox(this);
		m_x_rotation_spin_box->setValue(0);
		m_x_rotation_spin_box->setMinimum(-100.0);
		layout->addWidget(m_x_rotation_spin_box, 1, 4, 1, 2);

		m_y_rotation_label = new QLabel("y", this);
		layout->addWidget(m_y_rotation_label, 1, 6, 1, 1);

		m_y_rotation_spin_box = new QDoubleSpinBox(this);
		m_y_rotation_spin_box->setValue(0);
		m_y_rotation_spin_box->setMinimum(-100.0);
		layout->addWidget(m_y_rotation_spin_box, 1, 7, 1, 2);

		m_z_rotation_label = new QLabel("z", this);
		layout->addWidget(m_z_rotation_label, 1, 9, 1, 1);

		m_z_rotation_spin_box = new QDoubleSpinBox(this);
		m_z_rotation_spin_box->setValue(0);
		m_z_rotation_spin_box->setMinimum(-100.0);
		layout->addWidget(m_z_rotation_spin_box, 1, 10, 1, 2);

		//Scale
		m_scale = new QLabel("scale: ", this);
		layout->addWidget(m_scale, 2, 0, 1, 2);

		m_x_scale_label = new QLabel("x", this);
		layout->addWidget(m_x_scale_label, 2, 3, 1, 1);

		m_x_scale_spin_box = new QDoubleSpinBox(this);
		m_x_scale_spin_box->setValue(0);
		m_x_scale_spin_box->setMinimum(-100.0);
		layout->addWidget(m_x_scale_spin_box, 2, 4, 1, 2);

		m_y_scale_label = new QLabel("y", this);
		layout->addWidget(m_y_scale_label, 2, 6, 1, 1);

		m_y_scale_spin_box = new QDoubleSpinBox(this);
		m_y_scale_spin_box->setValue(0);
		layout->addWidget(m_y_scale_spin_box, 2, 7, 1, 2);

		m_z_scale_label = new QLabel("z", this);
		layout->addWidget(m_z_scale_label, 2, 9, 1, 1);

		m_z_scale_spin_box = new QDoubleSpinBox(this);
		m_z_scale_spin_box->setValue(0);
		layout->addWidget(m_z_scale_spin_box, 2, 10, 1, 2);
	}

	void TransformView::setupConnections()
	{
	}
}