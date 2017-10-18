#include "vfs.h"
#include <QFile>
#include <QTextStream>

namespace CGFF {

	QSharedPointer<VFS> VFS::s_instance = nullptr;

	void VFS::mount(const QString& virtualPath, const QString& physicalPath)
	{
		m_mountPoints[virtualPath].append(physicalPath);
	}

    QString VFS::getMountedPhysicalPath(const QString& virtualPath)
    {
        if (m_mountPoints.find(virtualPath) == m_mountPoints.end())
        {
            qFatal("Path is not mounted: %s", virtualPath);
        }

        return *m_mountPoints[virtualPath].begin();
    }

	void VFS::unmount(const QString& path)
	{
		m_mountPoints[path].clear();
	}

	bool VFS::resolvePhysicalPath(const QString& path, QString& outPhysicalPath)
	{
		QFile file;

		if (path[0] != '/')
		{
			outPhysicalPath = path;
			return file.exists(path);
		}

		QStringList dirs = path.split("/");

		const QString& virtualDir = dirs[1];

		if (m_mountPoints.find(virtualDir) == m_mountPoints.end() || m_mountPoints[virtualDir].empty())
		{
			qFatal("Path is not mounted: ", path);
			return false;
		}

		QString remainder = path.right(path.size() - virtualDir.size()-1);
		for (const QString& physicalPath : m_mountPoints[virtualDir])
		{
			QString path = physicalPath + remainder;
			if (file.exists(path))
			{
				outPhysicalPath = path;
				return true;
			}
		}
		return false;
	}

	QByteArray VFS::readFile(const QString& path)
	{
		QByteArray result;
		QString physicalPath;

		if (resolvePhysicalPath(path, physicalPath))
		{
			QFile file(physicalPath);

			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qFatal("Cannot read file: ", physicalPath);
			}
			result = file.readAll();
			file.close();
		}

		return result;
	}

	QString VFS::readTextFile(const QString& path)
	{
		QString result;
		QString physicalPath;

		if (resolvePhysicalPath(path, physicalPath))
		{
			QFile file(physicalPath);

			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qFatal("Cannot read file: ", physicalPath);
			}
			QTextStream fileIn(&file);
			result = fileIn.readAll();
			file.close();
		}

		return result;
	}

	bool VFS::writeFile(const QString& path, const QByteArray& buffer)
	{
		QString physicalPath;

		if (resolvePhysicalPath(path, physicalPath))
		{
			QFile file(physicalPath);
			file.open(QIODevice::WriteOnly);
			file.write(buffer);
			file.close();
			return true;
		}

		return false;
	}

	bool VFS::writeTextFile(const QString& path, const QString& text)
	{
		QString physicalPath;

		if (resolvePhysicalPath(path, physicalPath))
		{
			QFile file(physicalPath);
			file.open(QIODevice::WriteOnly);
			QTextStream out(&file);
			out << text;
			file.close();
			return true;
		}

		return false;
	}

	void VFS::init()
	{
		s_instance = QSharedPointer<VFS>(new VFS());
	}
	void VFS::shutdown()
	{
		s_instance.clear();
	}

}