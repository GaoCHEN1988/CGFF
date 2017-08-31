#ifndef CGFF_QT_MATHS_H
#define CGFF_QT_MATHS_H

#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QtMath>
#include <QByteArray>

namespace CGFF
{
	static QVector2D getMinBound(const QRect& rect)
	{
		return QVector2D(static_cast<float>(rect.x() - rect.width()), static_cast<float>(rect.y() - rect.height()));
	}
	static QVector2D getMaxBound(const QRect& rect)
	{
		return QVector2D(static_cast<float>(rect.x() + rect.width()), static_cast<float>(rect.y() + rect.height()));
	}
}

#endif