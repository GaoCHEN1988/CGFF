#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include "texture.h"

namespace CGFF {

    class Texture2D : public Texture
    {
    public:
        static QSharedPointer<Texture2D> Create(int width, int height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
        static QSharedPointer<Texture2D> CreateFromFile(const QString& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());     
        static QSharedPointer<Texture2D> createFromFile(const QString& name, const QString& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
    };

}

#endif