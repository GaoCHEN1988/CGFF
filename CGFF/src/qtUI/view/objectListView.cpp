#include "objectListView.h"
#include <QHBoxLayout>

namespace QTUI {

	ObjectListView::ObjectListView(QWidget *parent)
		: BaseView(parent)
		, m_treeView(nullptr)
	{
		init();
	}

	void ObjectListView::setModel(ResourceModel * model)
	{
		m_model = model;
		m_treeView->setModel(m_model);
	}

	void ObjectListView::onAddEntity(CGFF::EntityType type)
	{
		switch (type)
		{
		case CGFF::EntityType::CUBE:
		{
			emit entityAdded(m_model->addCube());
			break;
		}
		case CGFF::EntityType::PLANE:
		{
			emit entityAdded(m_model->addPlane());
			break;
		}
		case CGFF::EntityType::SPHERE:
		{
			emit entityAdded(m_model->addSphere());
			break;
		}
		}
	}

	void ObjectListView::init()
	{
		m_treeView = new QTreeView(this);

		//m_model = new ResourceModel(this);

		//m_treeView->setModel(m_model);

		QHBoxLayout *layout = new QHBoxLayout(this);

		layout->addWidget(m_treeView);
	}

}