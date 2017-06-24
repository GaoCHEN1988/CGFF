#ifndef TYPES_H
#define TYPES_H
#include "../maths/qtmaths.h"
#include <QDebug>

namespace CGFF {
#define RENDERER_MAX_SPRITES 60000
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

    //enum class UniformType
    //{
    //    NONE, FLOAT, INT, UINT,
    //    VEC2, VEC3, VEC4, 
    //    COLOR, POINT, POINTF,
    //    SIZE, SIZEF,
    //    MAT2x2, MAT2x3, MAT2x4, 
    //    MAT3x2, MAT3x3, MAT3x4, 
    //    MAT4x2, MAT4x3, MAT4x4,
    //    TRANDORM
    //};

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
        UniformData()
        {
            type = UniformType::NONE;
            data_pointer = nullptr;
        };
    };

}

#endif