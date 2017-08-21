#ifndef CGFF_TYPES_H
#define CGFF_TYPES_H
#include "../maths/qtmaths.h"

//#include <QDebug>
#include <QSharedPointer>
#include <QOpenGLShaderProgram>

namespace CGFF {

#define RENDERER_MAX_SPRITES 6000
    //#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITES_SIZE RENDERER_VERTEX_SIZE*4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITES_SIZE*RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES*6
#define RENDERER_MAX_TEXTURES 32

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

    //static void ResolveAndSetUniform(int loation, const UniformData& uniform, const QSharedPointer<QOpenGLShaderProgram>& shader)
    //{
    //    switch (uniform.type)
    //    {
    //    case UniformType::GLfloat:
    //    {
    //        shader->setUniformValue(loation, *(GLfloat *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::GLint:
    //    {
    //        shader->setUniformValue(loation, *(GLint *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::GLuint:
    //    {
    //        shader->setUniformValue(loation, *(GLuint *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QVector2D:
    //    {
    //        shader->setUniformValue(loation, *(QVector2D *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QVector3D:
    //    {
    //        shader->setUniformValue(loation, *(QVector3D *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QVector4D:
    //    {
    //        shader->setUniformValue(loation, *(QVector4D *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix2x2:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix2x2 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix2x3:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix2x3 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix2x4:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix2x4 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix3x2:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix3x2 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix3x3:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix3x3 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix3x4:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix3x4 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix4x2:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix4x2 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix4x3:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix4x3 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    case UniformType::QMatrix4x4:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix4x4 *)&uniform.data_pointer.data()[0]);
    //        break;
    //    }
    //    default:
    //        qDebug("Unknown uniform type!");
    //    }
    //};

    //static void ResolveAndSetUniform(int loation, const RendererUniform& uniform, const QSharedPointer<QOpenGLShaderProgram>& shader)
    //{
    //    switch (uniform.type)
    //    {
    //    case UniformType::GLfloat:
    //    {
    //        shader->setUniformValue(loation, *(GLfloat *)uniform.data);
    //        break;
    //    }
    //    case UniformType::GLint:
    //    {
    //        shader->setUniformValue(loation, *(GLint *)uniform.data);
    //        break;
    //    }
    //    case UniformType::GLuint:
    //    {
    //        shader->setUniformValue(loation, *(GLuint *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QVector2D:
    //    {
    //        shader->setUniformValue(loation, *(QVector2D *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QVector3D:
    //    {
    //        shader->setUniformValue(loation, *(QVector3D *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QVector4D:
    //    {
    //        shader->setUniformValue(loation, *(QVector4D *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix2x2:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix2x2 *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix2x3:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix2x3 *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix2x4:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix2x4 *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix3x2:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix3x2 *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix3x3:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix3x3 *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix3x4:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix3x4 *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix4x2:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix4x2 *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix4x3:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix4x3 *)uniform.data);
    //        break;
    //    }
    //    case UniformType::QMatrix4x4:
    //    {
    //        shader->setUniformValue(loation, *(QMatrix4x4 *)uniform.data);
    //        break;
    //    }
    //    default:
    //        qDebug("Unknown uniform type!");
    //    }
    //};
}

#endif