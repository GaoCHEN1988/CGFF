#ifndef CGFF_VFS_H
#define CGFF_VFS_H

#include <QHash>
#include <QtGlobal>
#include <QSharedPointer>
#include <QVector>

namespace CGFF {

	class VFS
	{
	public:
		void mount(const QString& virtualPath, const QString& physicalPath);
		void unmount(const QString& path);
		bool resolvePhysicalPath(const QString& path, QString& outPhysicalPath);

		QByteArray readFile(const QString& path);
		QString readTextFile(const QString& path);

		bool writeFile(const QString& path, const QByteArray& buffer);
		bool writeTextFile(const QString& path, const QString& text);
	public:
		static void init();
		static void shutdown();

		inline static QSharedPointer<VFS> get() 
		{ 
			if(s_instance.isNull())
				s_instance = QSharedPointer<VFS>(new VFS());

			return s_instance; 
		}

	private:
		static QSharedPointer<VFS> s_instance;
	private:
		QHash<QString, QVector<QString>> m_mountPoints;
	};
}

#endif
