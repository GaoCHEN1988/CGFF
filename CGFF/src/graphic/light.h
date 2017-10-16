#ifndef CGFF_LIGHT_H
#define CGFF_LIGHT_H

#include "maths/qtmaths.h"

namespace CGFF {
#if 0
    struct Light
    {
		QVector4D color;
        QVector3D position;
		float p0;
		QVector3D direction;
		float p1;
		QVector3D lightVector;
		float intensity;

		Light(const QVector3D& direction, float intensity = 1.0f, const QVector4D& color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
    };
#endif
    struct Light
    {
        QVector3D Position;
        QVector3D Color;
        float Linear;
        float Quadratic;
    };
}

#endif