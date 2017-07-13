#ifndef TYPES_H
#define TYPES_H
#include "../maths/qtmaths.h"
#include <QDebug>
#include <QSharedPointer>
#include <QOpenGLShaderProgram>

namespace CGFF {
#define RENDERER_MAX_SPRITES 6000
    //#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITES_SIZE RENDERER_VERTEX_SIZE*4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITES_SIZE*RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES*6
#define RENDERER_MAX_TEXTURES 32

#define SHADER_VERTEX_INDEX     0
#define SHADER_UV_INDEX         1
#define SHADER_MASK_UV_INDEX	2
#define SHADER_TID_INDEX        3
#define SHADER_MID_INDEX        4
#define SHADER_COLOR_INDEX      5

#define SHADER_UNIFORM_PROJECTION_MATRIX_NAME	"pr_matrix"
#define SHADER_UNIFORM_VIEW_MATRIX_NAME			"vw_matrix"
#define SHADER_UNIFORM_MODEL_MATRIX_NAME		"ml_matrix"

    struct VertexData
    {
        QVector3D vertex;
        QVector2D uv;
        QVector2D mask_uv;
        float tid;
        float mid;
        QVector4D color;
    };

#define RENDERER_VERTEX_SIZE	sizeof(VertexData)

    enum class UniformType
    {
        NONE,
        GLfloat,
        GLint,
        GLuint,
        QVector2D,
        QVector3D,
        QVector4D,
        QMatrix2x2,
        QMatrix2x3,
        QMatrix2x4,
        QMatrix3x2,
        QMatrix3x3,
        QMatrix3x4,
        QMatrix4x2,
        QMatrix4x3,
        QMatrix4x4,
    };

    struct UniformData
    {
        QSharedPointer<char> data_pointer;
        UniformType type;
        const char* uniform;
        UniformData()
        {
            type = UniformType::NONE;
            data_pointer = nullptr;
            uniform = "";
        };
    };

    struct RendererUniform
    {
        const char* uniform;
        void * data;
        UniformType type;
    };

    static void ResolveAndSetUniform(int loation, const UniformData& uniform, const QSharedPointer<QOpenGLShaderProgram>& shader)
    {
        switch (uniform.type)
        {
        case UniformType::GLfloat:
        {
            shader->setUniformValue(loation, *(GLfloat *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::GLint:
        {
            shader->setUniformValue(loation, *(GLint *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::GLuint:
        {
            shader->setUniformValue(loation, *(GLuint *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QVector2D:
        {
            shader->setUniformValue(loation, *(QVector2D *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QVector3D:
        {
            shader->setUniformValue(loation, *(QVector3D *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QVector4D:
        {
            shader->setUniformValue(loation, *(QVector4D *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix2x2:
        {
            shader->setUniformValue(loation, *(QMatrix2x2 *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix2x3:
        {
            shader->setUniformValue(loation, *(QMatrix2x3 *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix2x4:
        {
            shader->setUniformValue(loation, *(QMatrix2x4 *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix3x2:
        {
            shader->setUniformValue(loation, *(QMatrix3x2 *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix3x3:
        {
            shader->setUniformValue(loation, *(QMatrix3x3 *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix3x4:
        {
            shader->setUniformValue(loation, *(QMatrix3x4 *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix4x2:
        {
            shader->setUniformValue(loation, *(QMatrix4x2 *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix4x3:
        {
            shader->setUniformValue(loation, *(QMatrix4x3 *)&uniform.data_pointer.data()[0]);
            break;
        }
        case UniformType::QMatrix4x4:
        {
            shader->setUniformValue(loation, *(QMatrix4x4 *)&uniform.data_pointer.data()[0]);
            break;
        }
        default:
            qDebug("Unknown uniform type!");
        }
    };

    static void ResolveAndSetUniform(int loation, const RendererUniform& uniform, const QSharedPointer<QOpenGLShaderProgram>& shader)
    {
        switch (uniform.type)
        {
        case UniformType::GLfloat:
        {
            shader->setUniformValue(loation, *(GLfloat *)uniform.data);
            break;
        }
        case UniformType::GLint:
        {
            shader->setUniformValue(loation, *(GLint *)uniform.data);
            break;
        }
        case UniformType::GLuint:
        {
            shader->setUniformValue(loation, *(GLuint *)uniform.data);
            break;
        }
        case UniformType::QVector2D:
        {
            shader->setUniformValue(loation, *(QVector2D *)uniform.data);
            break;
        }
        case UniformType::QVector3D:
        {
            shader->setUniformValue(loation, *(QVector3D *)uniform.data);
            break;
        }
        case UniformType::QVector4D:
        {
            shader->setUniformValue(loation, *(QVector4D *)uniform.data);
            break;
        }
        case UniformType::QMatrix2x2:
        {
            shader->setUniformValue(loation, *(QMatrix2x2 *)uniform.data);
            break;
        }
        case UniformType::QMatrix2x3:
        {
            shader->setUniformValue(loation, *(QMatrix2x3 *)uniform.data);
            break;
        }
        case UniformType::QMatrix2x4:
        {
            shader->setUniformValue(loation, *(QMatrix2x4 *)uniform.data);
            break;
        }
        case UniformType::QMatrix3x2:
        {
            shader->setUniformValue(loation, *(QMatrix3x2 *)uniform.data);
            break;
        }
        case UniformType::QMatrix3x3:
        {
            shader->setUniformValue(loation, *(QMatrix3x3 *)uniform.data);
            break;
        }
        case UniformType::QMatrix3x4:
        {
            shader->setUniformValue(loation, *(QMatrix3x4 *)uniform.data);
            break;
        }
        case UniformType::QMatrix4x2:
        {
            shader->setUniformValue(loation, *(QMatrix4x2 *)uniform.data);
            break;
        }
        case UniformType::QMatrix4x3:
        {
            shader->setUniformValue(loation, *(QMatrix4x3 *)uniform.data);
            break;
        }
        case UniformType::QMatrix4x4:
        {
            shader->setUniformValue(loation, *(QMatrix4x4 *)uniform.data);
            break;
        }
        default:
            qDebug("Unknown uniform type!");
        }
    };
}

#endif