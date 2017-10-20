#include "explorerView.h"
#include "system/fileSystem/vfs.h"
#include "resource/shaderManager.h"

#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>

namespace QTUI {

	ExplorerView::ExplorerView(QWidget *parent)
		:QWidget(parent)
		, m_tabWidget(nullptr)
		, m_mkdirButton(nullptr)
		, m_rmButton(nullptr)
		, m_treeViews()
		, m_fileModels()
	{
        init();
	}

	void ExplorerView::init()
	{
		mountDirs();

		m_mkdirButton = new QPushButton(tr("Make Directory..."), this);
		m_rmButton = new QPushButton(tr("Remove"), this);
		QHBoxLayout *buttonLayout = new QHBoxLayout;
		buttonLayout->addWidget(m_mkdirButton);
		buttonLayout->addWidget(m_rmButton);

		QVBoxLayout *layout = new QVBoxLayout;
		layout->addWidget(m_tabWidget);
		layout->addLayout(buttonLayout);

		setLayout(layout);
		setWindowTitle("File System Model");

		connect(m_mkdirButton, SIGNAL(clicked()),
			this, SLOT(onMkdir()));
		connect(m_rmButton, SIGNAL(clicked()),
			this, SLOT(onRm()));
	}

	void ExplorerView::mountDirectory(const QString& path, const QString& name)
	{
		CGFF::VFS::get()->mount(name, path);
		QFileSystemModel* model = new QFileSystemModel(this);
		model->setRootPath(path);
		QTreeView * view = new QTreeView(this);
		view->setModel(model);
		view->setRootIndex(model->index(path));
        view->sortByColumn(0, Qt::SortOrder::AscendingOrder);
		view->header()->setStretchLastSection(true);
		view->header()->setSortIndicatorShown(true);
		view->setSortingEnabled(true);
#if QT_VERSION >= 0x050000
		view->header()->setSectionsClickable(true);
#else
		view->header()->setClickable(true);
#endif
		int index = m_tabWidget->addTab(view, name);

		m_treeViews[index] = view;
		m_fileModels[index] = model;
	}

	void ExplorerView::mountDirs()
	{
		CGFF::VFS::init();
		m_tabWidget = new QTabWidget(this);
		mountDirectory("Resources/", "resource");
		mountDirectory("src/graphic/shaders", "shaders");	
	}

    //Maybe should be somewhere else
    void ExplorerView::loadResources()
    {
        CGFF::ShaderManager::initilize();
    }

    void ExplorerView::onInitilize()
    {
        loadResources();
    }

	void ExplorerView::onMkdir()
	{
		int index = m_tabWidget->currentIndex();
		QModelIndex modelIndex = qobject_cast<QTreeView*>(m_tabWidget->currentWidget())->currentIndex();

		if (!modelIndex.isValid())
		{
			modelIndex = qobject_cast<QTreeView*>(m_tabWidget->currentWidget())->rootIndex();

			if (!modelIndex.isValid())
				return;
		}

		QString dirName = QInputDialog::getText(this,
			tr("Create Directory"),
			tr("Directory name"));

		if (!dirName.isEmpty()) {
			if (!m_fileModels[index]->mkdir(modelIndex, dirName).isValid()) {
				QMessageBox::information(this,
					tr("Create Directory"),
					tr("Failed to create the directory"));
			}
		}
	}

	void ExplorerView::onRm()
	{
		int index = m_tabWidget->currentIndex();
		QModelIndex modelIndex = qobject_cast<QTreeView*>(m_tabWidget->currentWidget())->currentIndex();
		if (!modelIndex.isValid()) {
			return;
		}
		bool ok;
		if (m_fileModels[index]->fileInfo(modelIndex).isDir()) {
			ok = m_fileModels[index]->rmdir(modelIndex);
		}
		else {
			ok = m_fileModels[index]->remove(modelIndex);
		}
		if (!ok) {
			QMessageBox::information(this,
				tr("Remove"),
				tr("Failed to remove %1").arg(m_fileModels[index]->fileName(modelIndex)));
		}
	}

}