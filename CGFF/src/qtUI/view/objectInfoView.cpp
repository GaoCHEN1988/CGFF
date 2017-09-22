#include "objectInfoView.h"
#include <QGridLayout>

namespace QTUI {

    ObjectInfoView::ObjectInfoView(QWidget *parent)
        : BaseView(parent)
        , m_transform_groupBox(nullptr)
        , m_material_groupBox(nullptr)
		, m_object_name_label(nullptr)
	{
		init();
	}

	void ObjectInfoView::init()
	{
		m_object_name_label = new QLabel("Object Name ", this);

		QGridLayout * layout = new QGridLayout(this);
		m_transform_groupBox = new QGroupBox("Transform", this);
		QGridLayout * transform_group_layout = new QGridLayout(m_transform_groupBox);
		m_transformView = new TransformView(this);
		transform_group_layout->addWidget(m_transformView);

        m_material_groupBox = new QGroupBox("Material", this);
        QGridLayout * material_group_layout = new QGridLayout(m_material_groupBox);


		layout->addWidget(m_object_name_label, 0, 0);
		layout->addWidget(m_transform_groupBox, 1, 0);
        layout->addWidget(m_material_groupBox, 2, 0);

		layout->setRowStretch(0, 1);
        layout->setRowStretch(1, 4);
        layout->setRowStretch(2, 4);
	}
}