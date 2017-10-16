#ifndef CGFF_GBUFFER_H
#define CGFF_GBUFFER_H

#include "maths/qtmaths.h"
#include "graphic/api/texture.h"

namespace CGFF {

    enum class TextureType : uint
    {
        Position = 0,
        Normal = 1,
        AlbedoSpec = 2
    };

    class GBuffer
    {
    public:
        virtual void bind(int mode = 0) = 0;
        virtual void unBind() = 0;
        virtual void clear() = 0;
        virtual void setReadBuffer(TextureType type) = 0;
        virtual void blitDepthBuffer() = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual QSize getSize() const = 0;
        virtual QSharedPointer<Texture> getTexture(TextureType type) const = 0;

        static QSharedPointer<GBuffer> create(int width, int height);
    protected:
        virtual void init() {};
    };


}

#endif