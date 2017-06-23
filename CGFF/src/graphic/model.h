#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include <QHash>

namespace CGFF {

    // TODO: Replace with uvec3, whenever that begins to exist
    struct IndexSet
    {
        uint position;
        uint uv;
        uint normal;

        bool operator==(const IndexSet& other) const
        {
            return position == other.position && uv == other.uv && normal == other.uv;
        }
    };

    inline uint qHash(const IndexSet &key)
    {
        return (key.position) ^ (key.normal << 14) ^ (key.uv << 23);
    }

    class Model : public IRenderable
    {
    public:
        // This eventually needs to be replaced by a global Asset Server.
        Model(const QString& path, QSharedPointer<MaterialInstance> materialInstance);
        ~Model();

        void render(Renderer3D& renderer) override;

        inline QSharedPointer<Mesh> getMesh() const { return m_mesh; }
    private:
        struct VertexSet
        {
            QVector<QVector3D> positions, normals;
            QVector<QVector2D> uvs;
        };
    
        //friend struct std::hash<IndexSet>;

        bool load(const QString& path);
        void insertVertex(QVector<Vertex>& vertices, QVector<uint>& indices, QHash<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);

    private:
        QSharedPointer<Mesh> m_mesh;
        QOpenGLBuffer vboBuf, indexBuf;
        QOpenGLVertexArrayObject vao;
        QSharedPointer<QOpenGLShaderProgram> m_shader;
    };

}

#endif