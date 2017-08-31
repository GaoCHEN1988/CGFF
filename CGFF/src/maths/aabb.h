#ifndef CGFF_AABB_H
#define CGFF_AABB_H

#include "qtmaths.h"

namespace CGFF 
{
	struct AABB
	{
		QVector3D min;
		QVector3D max;

		AABB();
		AABB(const QRect& rectangle);
		AABB(const QVector2D& min, const QVector2D& max);
		AABB(const QVector3D& min, const QVector3D& max);
		AABB(float x, float y, float width, float height);
		AABB(float x, float y, float z, float width, float height, float depth);

		bool intersects(const AABB& other) const;
		bool contains(const QVector2D& point) const;
		bool contains(const QVector3D& point) const;

		QVector3D center() const;

		bool operator==(const AABB& other) const;
		bool operator!=(const AABB& other) const;

		bool operator<(const AABB& other) const;
		bool operator>(const AABB& other) const;

		inline QVector3D getSize() const { return QVector3D(qFabs(max.x() - min.x()), qFabs(max.y() - min.y()), qFabs(max.z() - min.z())); }

		inline bool v3Larger(const QVector3D& v1, const QVector3D& v2) const
		{
			return v1.x() > v2.x() && v1.y()  > v2.y() && v1.z() > v2.z();
		};

		inline bool v3Smaller(const QVector3D& v1, const QVector3D& v2) const
		{
			return v1.x() < v2.x() && v1.y()  < v2.y() && v1.z() < v2.z();
		};
	};
}

#endif