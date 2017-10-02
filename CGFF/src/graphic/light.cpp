#include "light.h"

namespace CGFF 
{
	Light::Light(const QVector3D& direction, float intensity , const QVector4D& color)
		: direction(direction)
		, intensity(intensity)
		, color(color)
		, p0(0.0f)
		, p1(0.0f)
		, position()
		, lightVector()
        , projection()
        , view()
	{
	}
}