#ifndef CGFF_RENDER_COMMAND_H
#define CGFF_RENDER_COMMAND_H

#include "utils/types.h"
//#include "mesh.h"

namespace CGFF {

	class Mesh;

    struct RenderCommand
    {
        QSharedPointer<Mesh> mesh;
		QMatrix4x4 transform;
		QSharedPointer<Shader> shader;
        QVector<RendererUniform> uniforms;
    };

    static void SetRendererUniform(const RendererUniform& uniform, const QSharedPointer<QOpenGLShaderProgram>& shader)
    {
        //Need to test
        switch (uniform.type)
        {
        case UniformType::GLfloat:
        {
            shader->setUniformValue(uniform.uniform, *(GLfloat *)uniform.data);
            break;
        }
        case UniformType::GLint:
        {
            shader->setUniformValue(uniform.uniform, *(GLint *)uniform.data);
            break;
        }
        case UniformType::GLuint:
        {
            shader->setUniformValue(uniform.uniform, *(GLuint *)uniform.data);
            break;
        }
        case UniformType::QVector2D:
        {
            shader->setUniformValue(uniform.uniform, *(QVector2D *)uniform.data);
            break;
        }
        case UniformType::QVector3D:
        {
            shader->setUniformValue(uniform.uniform, *(QVector3D *)uniform.data);
            break;
        }
        case UniformType::QVector4D:
        {
            shader->setUniformValue(uniform.uniform, *(QVector4D *)uniform.data);
            break;
        }
        case UniformType::QMatrix2x2:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix2x2 *)uniform.data);
            break;
        }
        case UniformType::QMatrix2x3:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix2x3 *)uniform.data);
            break;
        }
        case UniformType::QMatrix2x4:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix2x4 *)uniform.data);
            break;
        }
        case UniformType::QMatrix3x2:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix3x2 *)uniform.data);
            break;
        }
        case UniformType::QMatrix3x3:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix3x3 *)uniform.data);
            break;
        }
        case UniformType::QMatrix3x4:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix3x4 *)uniform.data);
            break;
        }
        case UniformType::QMatrix4x2:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix4x2 *)uniform.data);
            break;
        }
        case UniformType::QMatrix4x3:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix4x3 *)uniform.data);
            break;
        }
        case UniformType::QMatrix4x4:
        {
            shader->setUniformValue(uniform.uniform, *(QMatrix4x4 *)uniform.data);
            break;
        }
        default:
            qDebug("Unknown uniform type!");
        }
    };
}

#endif
