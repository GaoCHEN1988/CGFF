#ifndef CGFF_SHADER_FACTORY_H
#define CGFF_SHADER_FACTORY_H

#include "utils/qtopengl.h"
#include "shader.h"

namespace CGFF {

    QSharedPointer<Shader> DefaultShader();
    QSharedPointer<Shader> SimpleShader();
    QSharedPointer<Shader> BasicLightShader();
	QSharedPointer<Shader> BatchRendererShader();
}

#endif
