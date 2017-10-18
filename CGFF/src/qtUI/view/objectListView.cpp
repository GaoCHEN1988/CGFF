#include "objectListView.h"
#include <QVBoxLayout>
#include <QGridLayout>

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
	}

    void ObjectListView::onElementChanged(const QModelIndex &index)
    {
        QString currentName = index.data(Qt::DisplayRole).toString();
        QString parentName =index.parent().data(Qt::DisplayRole).toString();
        QString topParent = getTopParent(index).data().toString();

        if (parentName == CGFF::ResourceManager::EntityHierarchyName)
        {
            m_model->onSetCurrentEntity(currentName);
        }

        if (parentName == CGFF::ResourceManager::LightHierarchyName)
        {
            m_model->onSetCurrentLight(currentName);
        }

        if (parentName == CGFF::ResourceManager::SkyBoxHierarchyName)
        {
            m_model->onSetCurrentSkyBox(currentName);
        }

        if (parentName == CGFF::ResourceManager::ModelHierarchyName)
        {
            m_model->onSetCurrentModel(currentName);
        }
    }

	void ObjectListView::init()
	{
		m_treeView = new QTreeView(this);

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