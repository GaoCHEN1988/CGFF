#ifndef MASK_H
#define MASK_H

#include "../maths/qtmaths.h"

//#include <QOpenGLTexture>
#include "api/texture2D.h"

namespace CGFF 
{
    class Mask
    {
    public:
        Mask(QSharedPointer<Texture2D> texture2D, const QMatrix4x4& transform = QMatrix4x4())
            : texture(texture2D)
            , transform(transform)
        {
            this->transform.scale(QVector3D((float)texture->getWidth() / (float)texture->getHeight(), 1.0f, 1.0f));
        }

    public:
        QSharedPointer<Texture> texture;
        QMatrix4x4 transform;
    };
}

#endif