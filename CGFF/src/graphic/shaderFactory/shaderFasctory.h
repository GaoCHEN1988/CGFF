#ifndef SHADER_FACTORY_H
#define SHADER_FACTORY_H

#include "utils/qtopengl.h"
#include <QOpenGLShaderProgram>

namespace CGFF {

    QSharedPointer<QOpenGLShaderProgram> DefaultShader();
    QSharedPointer<QOpenGLShaderProgram> SimpleShader();
    QSharedPointer<QOpenGLShaderProgram> BasicLightShader();
}

#endif
