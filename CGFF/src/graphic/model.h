#ifndef CGFF_MODEL_H
#define CGFF_MODEL_H

#include "mesh.h"
#include "resource/textureManager.h"
#include <QHash>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace CGFF {

    inline uint qHash(Vertex key)
    {
        return qHash(key.byteData());
    }

    class Model : public IRenderable
    {
    public:

        // This eventually needs to be replaced by a global Asset Server.
        Model(const QString& path, const QSharedPointer<MaterialInstance>& materialInstance = nullptr);
        virtual ~Model();

        void render(Renderer3D& renderer) override;

		inline const QVector<QSharedPointer<Mesh>>& getMeshes() const { return m_meshes; }
    private:

        //void insertVertex(const QVector3D& position, const QVector3D& normal, const QVector2D& uv, const QVector3D& binormal, const QVector3D& tangent);
		void processNode(aiNode *node, const aiScene *scene);
		void processMesh(aiMesh *mesh, const aiScene *scene);

		bool load(const QString& path);
        void loadMaterialTextures(aiMaterial *mat, aiTextureType type, QString typeName, QVector<MeshTexture>& outMeshTextureVector);
    private:

        QVector<QSharedPointer<Mesh>> m_meshes;
		QHash<Vertex, int> m_indexMapping;
        QString m_directoryPath;
        QSharedPointer<MaterialInstance> m_materialInstance;
    };

}

#endif