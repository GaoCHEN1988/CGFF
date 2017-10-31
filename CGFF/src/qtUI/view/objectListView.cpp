#include "objectListView.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMenu>

namespace QTUI {

	ObjectListView::ObjectListView(QWidget *parent)
		: BaseView(parent)
		, m_treeView(nullptr)
        , m_check_shadow_label(nullptr)
        , m_shadow_checkBox(nullptr)
        , m_renderer_label(nullptr)
        , m_renderer_combobox(nullptr)
	{
		init();
	}

	void ObjectListView::setModel(ResourceModel * model)
	{
		m_model = model;
		m_treeView->setModel(m_model);
        connect(m_treeView, &QTreeView::clicked, m_model, &ResourceModel::onCurrentSelectChanged);
	}

    void ObjectListView::onCustomContextMenu(const QPoint &point)
    {
        QModelIndex index = m_treeView->indexAt(point);
        if (index.isValid()) 
        {
            if (isEditableItem(index))
            {
                QMenu *menu = new QMenu(this);
                QAction *deleteItemAction = new QAction("Delete", menu);
                connect(deleteItemAction, &QAction::triggered, [=]() { m_model->onDeleteItem(index); });

                menu->addAction(deleteItemAction);
                menu->popup(m_treeView->mapToGlobal(point));
            }
        }
    }

	void ObjectListView::init()
	{
		m_treeView = new QTreeView(this);
        m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);

        QVBoxLayout *layout = new QVBoxLayout(this);
		layout->addWidget(m_treeView);

        QGridLayout * grid = new QGridLayout(this);
        m_check_shadow_label = new QLabel("Shadow", this);
        m_shadow_checkBox = new QCheckBox(this);
        m_renderer_label = new QLabel("Renderer", this);
        m_renderer_combobox = new QComboBox(this);
        m_renderer_combobox->addItem("Forward Renderer");

        grid->addWidget(m_renderer_label, 0, 0, 1, 1);
        grid->addWidget(m_renderer_combobox, 0, 1, 1, 2);

        grid->addWidget(m_check_shadow_label, 1, 0, 1, 1);
        grid->addWidget(m_shadow_checkBox, 1, 1, 1, 1);

        layout->addLayout(grid);

        setupConnections();
	}

    void ObjectListView::setupConnections()
    {
        //QObject::connect(m_treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ObjectListView::onElementChanged, Qt::DirectConnection);
        connect(m_treeView, &QTreeView::customContextMenuRequested, this, &ObjectListView::onCustomContextMenu);
    }

    bool ObjectListView::isEditableItem(const QModelIndex &index)
    {
        QString currentName = index.data(Qt::DisplayRole).toString();
        QString parentName = index.parent().data(Qt::DisplayRole).toString();

        if (parentName == CGFF::ResourceManager::EntityHierarchyName 
            || parentName == CGFF::ResourceManager::LightHierarchyName
            || parentName == CGFF::ResourceManager::SkyBoxHierarchyName
            || parentName == CGFF::ResourceManager::ModelHierarchyName)
        {
            return true;
        }

        return false;
    }
}