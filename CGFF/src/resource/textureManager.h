#ifndef CGFF_TEXTURE_MANAGER_H
#define CGFF_TEXTURE_MANAGER_H

#include "graphic/api/texture.h"

namespace CGFF {

    class TextureManager
    {
    public:
        TextureManager() = delete;

        //Texture resource
        static QSharedPointer<Texture> getTexture2D(const QString& path);
        static void removeTexture2D(const QString& path);

        static QMap<QString, QSharedPointer<Texture>> m_textureResources;
    };
}

#endif

