#include "explorerView.h"
#include "system/fileSystem/vfs.h"

#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>

namespace QTUI {

	ExplorerView::ExplorerView(QWidget *parent)
		:QWidget(parent)
	{
		CGFF::VFS::init();
		CGFF::VFS::get()->mount("resource", "Resources/");
		CGFF::VFS::get()->mount("pbr", "Resources/pbr");
		CGFF::VFS::get()->mount("shaders", "src/graphic/shaders");

		m_fileModel = new QFileSystemModel(this);
		m_fileModel->setRootPath("Resources/");

		m_treeView = new QTreeView(this);
		m_treeView->setModel(m_fileModel);
		m_treeView->setRootIndex(m_fileModel->index("Resources/"));

		m_treeView->header()->setStretchLastSection(true);
		m_treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
		m_treeView->header()->setSortIndicatorShown(true);
#if QT_VERSION >= 0x050000
		m_treeView->header()->setSectionsClickable(true);
#else
		m_treeView->header()->setClickable(true);
#endif

		m_mkdirButton = new QPushButton(tr("Make Directory..."), this);
		m_rmButton = new QPushButton(tr("Remove"), this);
		QHBoxLayout *buttonLayout = new QHBoxLayout;
		buttonLayout->addWidget(m_mkdirButton);
		buttonLayout->addWidget(m_rmButton);

		QVBoxLayout *layout = new QVBoxLayout;
		layout->addWidget(m_treeView);
		layout->addLayout(buttonLayout);

		setLayout(layout);
		setWindowTitle("File System Model");

		connect(m_mkdirButton, SIGNAL(clicked()),
			this, SLOT(onMkdir()));
		connect(m_rmButton, SIGNAL(clicked()),
			this, SLOT(onRm()));

	}

	void ExplorerView::onMkdir()
	{
		QModelIndex index = m_treeView->currentIndex();
		if (!index.isValid()) {
			return;
		}
		QString dirName = QInputDialog::getText(this,
			tr("Create Directory"),
			tr("Directory name"));
		if (!dirName.isEmpty()) {
			if (!m_fileModel->mkdir(index, dirName).isValid()) {
				QMessageBox::information(this,
					tr("Create Directory"),
					tr("Failed to create the directory"));
			}
		}
	}

	void ExplorerView::onRm()
	{
		QModelIndex index = m_treeView->currentIndex();
		if (!index.isValid()) {
			return;
		}
		bool ok;
		if (m_fileModel->fileInfo(index).isDir()) {
			ok = m_fileModel->rmdir(index);
		}
		else {
			ok = m_fileModel->remove(index);
		}
		if (!ok) {
			QMessageBox::information(this,
				tr("Remove"),
				tr("Failed to remove %1").arg(m_fileModel->fileName(index)));
		}
	}

}