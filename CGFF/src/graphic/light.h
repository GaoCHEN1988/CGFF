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

    enum class LightType
    {
        DIRECTIONAL,
        SPOT,
        POINT
    };

    struct Light
    {
        QVector4D color;
        QVector3D position;
        QVector3D direction;
        QVector3D lightVector;
        float intensity;

        Light(const QVector3D& direction = QVector3D(0.0, 0.0, 0.0),
              const QVector3D& position = QVector3D(0.0, 20.0, 0.0),
              float intensity = 1.0f, 
              const QVector4D& color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f))
            : direction(direction)
            , position(position)
            , color(color)
            , lightVector()
            , intensity(intensity)
        {
        }
    };
}

#endif