#include "objectInfoView.h"
#include <QGridLayout>

namespace QTUI {

    ObjectInfoView::ObjectInfoView(QWidget *parent)
        : BaseView(parent)
        , m_transform_groupBox(nullptr)
        , m_material_groupBox(nullptr)
		, m_object_name_label(nullptr)
        , m_transformView(nullptr)
        , m_materialView(nullptr)
	{
		init();
	}

    void ObjectInfoView::setModel(ResourceModel * model)
    {
        m_model = model;
        m_transformView->setModel(model);
        m_materialView->setModel(model);

        setupConnections();
    }

    void ObjectInfoView::onCurrentEntitySet(const QString& name, const CGFF::UiTransformVec& transform)
    {
        m_object_name_label->setText(name);
        m_transformView->onCurrentEntitySet(name, transform);
		m_materialView->onCurrentEntitySet(name);
    }

    void ObjectInfoView::onCurrentModelObjectSet(const QString& name, const CGFF::UiTransformVec& transform)
    {
        m_object_name_label->setText(name);
        m_transformView->onCurrentModelObjectSet(name, transform);
        m_materialView->onCurrentModelObjectSet(name);
    }

	void ObjectInfoView::onCurrentItemNameChanged(const QString& name)
	{
		m_object_name_label->setText(name);
	}

    void ObjectInfoView::onSetEmptyItem()
    {
        m_object_name_label->setText("");
        m_transformView->onSetEmpty();
        m_materialView->onSetEmpty();
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
        m_materialView = new MaterialView(this);
        material_group_layout->addWidget(m_materialView);

        layout->addWidget(m_object_name_label, 0, 0);
        layout->addWidget(m_transform_groupBox, 1, 0);
        layout->addWidget(m_material_groupBox, 2, 0);

        layout->setRowStretch(0, 1);
        layout->setRowStretch(1, 4);
        layout->setRowStretch(2, 4);
    }

    void ObjectInfoView::setupConnections()
    {
        connect(m_model, &ResourceModel::currentEntitySet, this, &ObjectInfoView::onCurrentEntitySet);
        connect(m_model, &ResourceModel::currentModelObjectSet, this, &ObjectInfoView::onCurrentModelObjectSet);
        connect(m_model, &ResourceModel::currentItemNameChanged, this, &ObjectInfoView::onCurrentItemNameChanged);
        connect(m_model, &ResourceModel::setEmptyItem, this, &ObjectInfoView::onSetEmptyItem);
    }
}