#include "shaderProgram.h"

namespace CGFF {

    ShaderProgram::ShaderProgram(QString name, QString vertexFile, QString fragmentFile)
        : m_name(name)
        , m_vertexFile(vertexFile)
        , m_fragmentFile(fragmentFile)
    {
        load();
    }

    void ShaderProgram::load()
    {
        if (!addShaderFromSourceFile(QOpenGLShader::Vertex, m_vertexFile))
            qFatal("Error:Can't compile vertex shader");
        if (!addShaderFromSourceFile(QOpenGLShader::Fragment, m_fragmentFile))
            qFatal("Error:Can't compile vertex shader");
        if (!link())
            qFatal("Error:Can't link shaders");
    }

    void ShaderProgram::reload()
    {
        removeAllShaders();
        load();
    }

}