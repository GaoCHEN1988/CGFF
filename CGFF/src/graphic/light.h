#ifndef LIGHT_H
#define LIGHT_H

#include "maths/qtmaths.h"

namespace CGFF {
    struct Light
    {
        QVector3D position;
        float attenuation;
        QVector4D color;
    };

}

#endif