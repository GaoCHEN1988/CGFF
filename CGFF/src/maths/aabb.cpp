#include "aabb.h"

namespace CGFF
{
	AABB::AABB()
		: min(QVector3D()), max(QVector3D())
	{
	}

	AABB::AABB(const QRect& rectangle)
		: min(getMinBound(rectangle)), max(getMaxBound(rectangle))
	{
	}

	AABB::AABB(const QVector2D& min, const QVector2D& max)
		: min(QVector3D(min)), max(QVector3D(max))
	{
	}

	AABB::AABB(const QVector3D& min, const QVector3D& max)
		: min(min), max(max)
	{
	}

	AABB::AABB(float x, float y, float width, float height)
		: min(QVector3D(x, y, 0.0f)), max(QVector3D(width, height, 0.0f))
	{
	}

	AABB::AABB(float x, float y, float z, float width, float height, float depth)
		: min(QVector3D(x, y, z)), max(QVector3D(width, height, depth))
	{
	}

	bool AABB::intersects(const AABB& other) const
	{
		return (v3Larger(max, other.min) && v3Smaller(min, other.max)) || (v3Larger(min, other.max) && v3Smaller(max, other.min));
	}

	bool AABB::contains(const QVector2D& point) const
	{
		return v3Larger(QVector3D(point), min) && v3Smaller(QVector3D(point), max);
	}

	bool AABB::contains(const QVector3D& point) const
	{
		return v3Larger(point, min) && v3Smaller(point, max);
	}

	QVector3D AABB::center() const
	{
		return (max + min) * 0.5f;
	}

	bool AABB::operator==(const AABB& other) const
	{
		return min == other.min && max == other.max;
	}

	bool AABB::operator!=(const AABB& other) const
	{
		return !(*this == other);
	}

	bool AABB::operator<(const AABB& other) const
	{
		return v3Smaller(max, other.min);
	}

	bool AABB::operator>(const AABB& other) const
	{
		return v3Larger(min, other.max);
	}
}