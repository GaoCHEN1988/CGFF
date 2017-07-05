#include "shaderFasctory.h"

namespace CGFF {
    QSharedPointer<QOpenGLShaderProgram> DefaultShader()
    {
        QSharedPointer<QOpenGLShaderProgram> shader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);

#ifdef OPENGL_ES
        // load and compile vertex shader
        bool success = shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader_es/SimpleVertexShader.vert");
        // load and compile fragment shader
        success = shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader_es/SimpleFragmentShader.frag");
#else
        // load and compile vertex shader
        bool success = shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader/SimpleVertexShader.vert");
        // load and compile fragment shader
        success = shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader/SimpleFragmentShader.frag");
#endif
        shader->link();

        return shader;
    }

    QSharedPointer<QOpenGLShaderProgram> SimpleShader()
    {
        return nullptr;
    }

    QSharedPointer<QOpenGLShaderProgram> BasicLightShader()
    {
        return nullptr;
    }
}