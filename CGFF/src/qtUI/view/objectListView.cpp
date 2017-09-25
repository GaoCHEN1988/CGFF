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

    void ObjectListView::onElementChanged(const QModelIndex &index)
    {
        QString currentName = index.data(Qt::DisplayRole).toString();
        QString parentName =index.parent().data(Qt::DisplayRole).toString();
        QString topParent = getTopParent(index).data().toString();

        if (parentName == CGFF::ResourceManager::getEntityHierarchyName())
        {
            m_model->onSetCurrentEntity(currentName);
        }

        if (parentName == CGFF::ResourceManager::getLightHierarchyName())
        {
            m_model->onSetCurrentLight(currentName);
        }

        if (parentName == CGFF::ResourceManager::getSkyBoxHierarchyName())
        {
            m_model->onSetCurrentSkyBox(currentName);
        }
    }

	void ObjectListView::init()
	{
		m_treeView = new QTreeView(this);

		QHBoxLayout *layout = new QHBoxLayout(this);

		layout->addWidget(m_treeView);

        setupConnections();
	}

    void ObjectListView::setupConnections()
    {
        //QObject::connect(m_treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ObjectListView::onElementChanged, Qt::DirectConnection);
        QObject::connect(m_treeView, &QTreeView::clicked, this, &ObjectListView::onElementChanged);
    }

    QModelIndex ObjectListView::getTopParent(QModelIndex itemIndex)
    {
        QModelIndex secondItem = itemIndex;
        while (itemIndex.parent().isValid())
        {
            secondItem = itemIndex.parent();
            itemIndex = secondItem;
        }
        if (secondItem.column() != 0)
        {
            secondItem = secondItem.sibling(secondItem.row(), 0);
        }
        return secondItem;
    }
}