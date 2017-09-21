#include "objectInfoView.h"
#include <QGridLayout>

namespace QTUI {

    ObjectInfoView::ObjectInfoView(QWidget *parent)
        : QWidget(parent)
        , m_transform_groupBox(nullptr)
        , m_material_groupBox(nullptr)
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
		, m_object_name(nullptr)
	{
		init();
	}

    void ObjectInfoView::setCurrentObject()
    {
    }

	void ObjectInfoView::init()
	{
		QGridLayout * layout = new QGridLayout(this);
		m_transform_groupBox = new QGroupBox("Transform", this);
		QGridLayout * transform_group_layout = new QGridLayout(m_transform_groupBox);

        //Position
        m_position = new QLabel("position: ", m_transform_groupBox);
        transform_group_layout->addWidget(m_position, 0, 0, 1, 2);

		m_x_label = new QLabel("x", m_transform_groupBox);
		transform_group_layout->addWidget(m_x_label, 0, 3, 1, 1);

        m_x_spin_box = new QSpinBox(m_transform_groupBox);
        m_x_spin_box->setValue(0);
        transform_group_layout->addWidget(m_x_spin_box, 0, 4, 1, 2);

		m_y_label = new QLabel("y", m_transform_groupBox);
		transform_group_layout->addWidget(m_y_label, 0, 6, 1, 1);

        m_y_spin_box = new QSpinBox(m_transform_groupBox);
        m_y_spin_box->setValue(0);
        transform_group_layout->addWidget(m_y_spin_box, 0, 7, 1, 2);

		m_z_label = new QLabel("z", m_transform_groupBox);
		transform_group_layout->addWidget(m_z_label, 0, 9, 1, 1);

		m_z_spin_box = new QSpinBox(m_transform_groupBox);
		m_z_spin_box->setValue(0);
		transform_group_layout->addWidget(m_z_spin_box, 0, 10, 1, 2);

        //Rotation
        m_rotation = new QLabel("rotatiom: ", m_transform_groupBox);
        transform_group_layout->addWidget(m_rotation, 1, 0, 1, 2);

        m_x_rotation_label = new QLabel("x", m_transform_groupBox);
        transform_group_layout->addWidget(m_x_rotation_label, 1, 3, 1, 1);

        m_x_rotation_spin_box = new QSpinBox(m_transform_groupBox);
        m_x_rotation_spin_box->setValue(0);
        transform_group_layout->addWidget(m_x_rotation_spin_box, 1, 4, 1, 2);

        m_y_rotation_label = new QLabel("y", m_transform_groupBox);
        transform_group_layout->addWidget(m_y_rotation_label, 1, 6, 1, 1);

        m_y_rotation_spin_box = new QSpinBox(m_transform_groupBox);
        m_y_rotation_spin_box->setValue(0);
        transform_group_layout->addWidget(m_y_rotation_spin_box, 1, 7, 1, 2);

        m_z_rotation_label = new QLabel("z", m_transform_groupBox);
        transform_group_layout->addWidget(m_z_rotation_label, 1, 9, 1, 1);

        m_z_rotation_spin_box = new QSpinBox(m_transform_groupBox);
        m_z_rotation_spin_box->setValue(0);
        transform_group_layout->addWidget(m_z_rotation_spin_box, 1, 10, 1, 2);

        //Scale
        m_scale = new QLabel("scale: ", m_transform_groupBox);
        transform_group_layout->addWidget(m_scale, 2, 0, 1, 2);

        m_x_scale_label = new QLabel("x", m_transform_groupBox);
        transform_group_layout->addWidget(m_x_scale_label, 2, 3, 1, 1);

        m_x_scale_spin_box = new QSpinBox(m_transform_groupBox);
        m_x_scale_spin_box->setValue(0);
        transform_group_layout->addWidget(m_x_scale_spin_box, 2, 4, 1, 2);

        m_y_scale_label = new QLabel("y", m_transform_groupBox);
        transform_group_layout->addWidget(m_y_scale_label, 2, 6, 1, 1);

        m_y_scale_spin_box = new QSpinBox(m_transform_groupBox);
        m_y_scale_spin_box->setValue(0);
        transform_group_layout->addWidget(m_y_scale_spin_box, 2, 7, 1, 2);

        m_z_scale_label = new QLabel("z", m_transform_groupBox);
        transform_group_layout->addWidget(m_z_scale_label, 2, 9, 1, 1);

        m_z_scale_spin_box = new QSpinBox(m_transform_groupBox);
        m_z_scale_spin_box->setValue(0);
        transform_group_layout->addWidget(m_z_scale_spin_box, 2, 10, 1, 2);

		m_object_name = new QLabel("Object Name ", this);

        m_material_groupBox = new QGroupBox("Material", this);
        QGridLayout * material_group_layout = new QGridLayout(m_material_groupBox);


		layout->addWidget(m_object_name, 0, 0);
		layout->addWidget(m_transform_groupBox, 1, 0);
        layout->addWidget(m_material_groupBox, 2, 0);

		layout->setRowStretch(0, 1);
        layout->setRowStretch(1, 4);
        layout->setRowStretch(2, 4);
	}
}