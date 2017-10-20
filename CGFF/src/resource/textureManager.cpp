#include "textureManager.h"
#include "graphic/api/texture2D.h"
#include "graphic/api/textureCube.h"
#include "graphic/api/textureDepth.h"
#include "system/fileSystem/vfs.h"

namespace CGFF {

    QMap<QString, QSharedPointer<Texture>> TextureManager::m_textureResources;

    QSharedPointer<Texture> TextureManager::getTexture2D(const QString& path)
    {
        QString filename;
        if (!VFS::get()->resolvePhysicalPath(path, filename))
            qFatal("Can't load image file: ", path);

        auto lookup = m_textureResources.find(filename);
        if (lookup != m_textureResources.end())
        {
            return lookup.value();
        }
        else
        {
            m_textureResources.insert(filename, Texture2D::createFromFile(filename));
            return m_textureResources[filename];
        }
    }

    QSharedPointer<Texture> TextureManager::getTextureCube(const QStringList& pathes)
    {
        QString filename;
        if (!VFS::get()->resolvePhysicalPath(pathes[0], filename))
            qFatal("Can't load image file: ", pathes[0]);

        auto lookup = m_textureResources.find(filename);
        if (lookup != m_textureResources.end())
        {
            return lookup.value();
        }
        else
        {
            m_textureResources.insert(filename, TextureCube::createFromFiles(pathes));
            return m_textureResources[filename];
        }
    }

    void TextureManager::removeTexture2D(const QString& path)
    {
        QString filename;
        if (!VFS::get()->resolvePhysicalPath(path, filename))
            qFatal("Can't load image file: ", path);

        auto lookup = m_textureResources.find(filename);
        if (lookup != m_textureResources.end())
        {
            m_textureResources.remove(filename);
        }
    }
}