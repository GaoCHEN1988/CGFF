#ifndef CGFF_TEXTURE_2D_H
#define CGFF_TEXTURE_2D_H

#include "texture.h"

namespace CGFF {

    class Texture2D : public Texture
    {
    public:
        static QSharedPointer<Texture2D> create(int width, int height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
        static QSharedPointer<Texture2D> createFromFile(const QString& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());     
		static QSharedPointer<Texture2D> createFromFile(const QString& name, const QString& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
        static QSharedPointer<Texture2D> createFromImage(const QImage& image, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
        static QSharedPointer<Texture2D> create(int width, int height, const void *data, TextureParameters parameters = TextureParameters());
    };

}

#endif