#include "textureManager.h"
#include "graphic/api/texture2D.h"
#include "graphic/api/textureCube.h"
#include "graphic/api/textureDepth.h"

namespace CGFF {

    QMap<QString, QSharedPointer<Texture>> TextureManager::m_textureResources;

    QSharedPointer<Texture> TextureManager::getTexture2D(const QString& path)
    {
        auto lookup = m_textureResources.find(path);
        if (lookup != m_textureResources.end())
        {
            return lookup.value();
        }
        else
        {
            m_textureResources.insert(path, Texture2D::createFromFile(path));
            return m_textureResources[path];
        }
    }

    void TextureManager::removeTexture2D(const QString& path)
    {
        auto lookup = m_textureResources.find(path);
        if (lookup != m_textureResources.end())
        {
            m_textureResources.remove(path);
        }
    }
}