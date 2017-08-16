#ifndef CGFF_SHADER_FACTORY_H
#define CGFF_SHADER_FACTORY_H

#include "utils/qtopengl.h"
#include "shader.h"
#include <QOpenGLShaderProgram>

namespace CGFF {

    QSharedPointer<QOpenGLShaderProgram> DefaultShader();
    QSharedPointer<QOpenGLShaderProgram> SimpleShader();
    QSharedPointer<QOpenGLShaderProgram> BasicLightShader();
	QSharedPointer<Shader> BatchRendererShader();
}

#endif
