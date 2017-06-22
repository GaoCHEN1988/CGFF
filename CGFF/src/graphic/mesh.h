#ifndef MESH_H
#define MESH_H
#include "utils/qtopengl.h"
#include "maths/qtmaths.h"
#include "material.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

namespace CGFF {

    class Renderer3D;

    struct Vertex
    {
        QVector3D position;
        QVector3D normal;
        QVector2D uv;
    };

    class Mesh
    {
    private:
        QOpenGLVertexArrayObject* m_vertexArray;
        QOpenGLBuffer* m_indexBuffer;
        QSharedPointer<MaterialInstance> m_materialInstance;
    public:
        Mesh(QOpenGLVertexArrayObject* vertexArray, QOpenGLBuffer* indexBuffer, QSharedPointer<MaterialInstance>& materialInstance);
        ~Mesh();

        inline QSharedPointer<MaterialInstance>& getMaterialInstance() { return m_materialInstance; }

        void render(Renderer3D& renderer);
    };
}

#endif
