#ifndef QTOPENGL_H
#define QTOPENGL_H
#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <QSharedPointer>
#include <QSize>
#include <QFont>

namespace CGFF
{
    extern QOpenGLFunctions *GL;
    extern QSize openglWidgetSize;
}


#endif