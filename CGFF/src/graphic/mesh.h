#ifndef CGFF_MESH_H
#define CGFF_MESH_H
#include "utils/qtopengl.h"
#include "maths/qtmaths.h"
#include "api/vertexArray.h"
#include "api/indexBuffer.h"
#include "material.h"
#include "irenderable.h"
#include <QDataStream>

namespace CGFF {

    class Renderer3D;

    struct Vertex
    {
        QVector3D position;
        QVector3D normal;
        QVector2D uv;
		QVector3D binormal;
		QVector3D tangent;

		QByteArray byteData()
		{
			QByteArray baResult;
			QDataStream dsOut(&baResult, QIODevice::ReadWrite);  
			dsOut << position << normal << uv<< binormal<< tangent;
			return baResult;
		};

		bool operator==(const Vertex& other) const
		{
			return position == other.position && normal == other.normal && uv == other.uv && binormal == other.binormal && tangent == other.tangent;
		};
    };

    struct MeshTexture
    {
        QSharedPointer<Texture> texture;
        QString type;
    };

    const QString pbr_diffuseMap = "texture_diffuse";
    const QString pbr_specularMap = "texture_specular";
    const QString pbr_normalMap = "texture_normal";
    const QString pbr_heightMap = "texture_height";

    class Mesh : public IRenderable
    {
    public:
		Mesh(const QSharedPointer<VertexArray>& vertexArray, 
             const QSharedPointer<IndexBuffer>& indexBuffer,
             const QSharedPointer<MaterialInstance>& materialInstance,
             const QVector<MeshTexture>& textures = QVector<MeshTexture>(),
            DrawMode mode = DrawMode::TRIANGLES);

		Mesh(QSharedPointer<Mesh> mesh, DrawMode mode = DrawMode::TRIANGLES);
        virtual ~Mesh();

        inline void setMaterial(const QSharedPointer<MaterialInstance>& materialInstance) { m_materialInstance = materialInstance; }
        inline QSharedPointer<MaterialInstance>& getMaterialInstance() { return m_materialInstance; }
        inline void setInvertedNormal(bool inverted)
        {
            m_isInvertedNormal = inverted;
        }
        inline bool isInvertedNormal()
        {
            return m_isInvertedNormal;
        }
        void render(Renderer3D& renderer) override;
        void bind();
        void unBind();
        void draw();

	private:
		QSharedPointer<VertexArray> m_vertexArray;
		QSharedPointer<IndexBuffer> m_indexBuffer;
        QSharedPointer<MaterialInstance> m_materialInstance;
        QVector<MeshTexture> m_textures;
		DrawMode m_drawMode;
        bool m_isInvertedNormal;
    };
}

#endif
