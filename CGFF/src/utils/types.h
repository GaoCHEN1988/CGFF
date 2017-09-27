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
		STRUCT
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

	enum class EntityType
	{
		CUBE,
		PLANE,
		SPHERE
	};
}

#endif