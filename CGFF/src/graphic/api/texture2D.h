#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include "texture.h"

namespace CGFF {

    class Texture2D : public QOpenGLTexture
    {
    public:
		Texture2D(QOpenGLTexture::Target target = Target2D);
        //virtual void setData(const void* pixels) = 0;
        //virtual void setData(uint color) = 0;

        //virtual uint getWidth() const = 0;
        //virtual uint getHeight() const = 0;
    public:
        //static Texture2D* Create(uint width, uint height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
        //static Texture2D* CreateFromFile(const QString& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
        //static Texture2D* CreateFromFile(const QString& filepath, TextureLoadOptions loadOptions);
        //static Texture2D* CreateFromFile(const QString& name, const QString& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
        //static Texture2D* CreateFromFile(const QString& name, const QString& filepath, TextureLoadOptions loadOptions);

        static QSharedPointer<Texture2D> createFromFile(const QString& name, const QString& filepath);
    };

}

#endif