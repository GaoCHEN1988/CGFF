#ifndef CGFF_LIGHT_H
#define CGFF_LIGHT_H

#include "maths/qtmaths.h"

namespace CGFF {
    struct Light
    {
		QVector4D color;
        QVector3D position;
		float p0;
		QVector3D direction;
		float p1;
		QVector3D lightVector;
		float intensity;
        QMatrix4x4 projection;
        QMatrix4x4 view;

		Light(const QVector3D& direction, float intensity = 1.0f, const QVector4D& color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
    };

}

#endif