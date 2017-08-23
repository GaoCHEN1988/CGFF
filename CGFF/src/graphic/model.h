#ifndef CGFF_MODEL_H
#define CGFF_MODEL_H

#include "mesh.h"
#include <QHash>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

		struct MeshStruct
		{
			QVector<Vertex> vertices;
			QVector<uint> indices;

			void clear()
			{
				vertices.clear();
				indices.clear();
			}
		};

        // This eventually needs to be replaced by a global Asset Server.
        Model(const QString& path, QSharedPointer<MaterialInstance> materialInstance = nullptr);
        virtual ~Model();

        void render(Renderer3D& renderer) override;

		inline QSharedPointer<Mesh> getMesh() const { return m_mesh; }
		//inline const QVector<QSharedPointer<Mesh>>& getMeshes() const { return m_meshes; }
    private:
        struct VertexSet
        {
            QVector<QVector3D> positions, normals;
            QVector<QVector2D> uvs;
        };
    
        //friend struct std::hash<IndexSet>;

        //void insertVertex(QVector<Vertex>& vertices, QVector<uint>& indices, QHash<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);
		void processNode(aiNode *node, const aiScene *scene);
		void processMesh(aiMesh *mesh, const aiScene *scene);

		bool load(const QString& path);

    private:
		//QVector<QSharedPointer<Mesh>> m_meshes;
		QSharedPointer<Mesh> m_mesh;
		MeshStruct m_meshStruct;
    };

}

#endif