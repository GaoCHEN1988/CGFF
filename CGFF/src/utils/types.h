#ifndef TYPES_H
#define TYPES_H
#include "../maths/qtmaths.h"
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
}

#endif