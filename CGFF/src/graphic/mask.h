#ifndef MASK_H
#define MASK_H

#include "../maths/qtmaths.h"

#include <QOpenGLTexture>

namespace CGFF 
{
    class Mask
    {
    public:
        Mask(QSharedPointer<QOpenGLTexture> gltexture, const QMatrix4x4& transform = QMatrix4x4())
            : texture(gltexture)
            , transform(transform)
        {
            this->transform.scale(QVector3D((float)texture->width() / (float)texture->height(), 1.0f, 1.0f));
        }

    public:
        QSharedPointer<QOpenGLTexture> texture;
        QMatrix4x4 transform;
    };
}

#endif