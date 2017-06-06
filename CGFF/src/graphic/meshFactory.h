#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include "../maths/qtmaths.h"
#include "../utils/qtopengl.h"

namespace CGFF {
    namespace MeshFactory {


        GLuint CreateQuad(float x, float y, float width, float height);
        GLuint CreateQuad(const QVector2D& position, const QVector2D& size);


    }
}

#endif
