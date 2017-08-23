#ifndef CGFF_QTOPENGL_H
#define CGFF_QTOPENGL_H

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <QSize>
#include <QFont>

namespace CGFF
{
    extern QOpenGLFunctions_4_4_Core *GL;
	extern QSize g_openglWidgetSize;

#ifdef DEBUG
#define GLCall(x) {\
	x;\
	if (CGFF::GL->glGetError() != GL_NO_ERROR)\
	{\
		qFatal("Opengl error!");\
	}}
#else
#define GLCall(x) x
#endif
}


#endif