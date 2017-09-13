#ifndef CGFF_MESH_FACTORY_H
#define CGFF_MESH_FACTORY_H

#include "maths/qtmaths.h"
#include "utils/qtopengl.h"
#include "utils/types.h"
#include "mesh.h"
#include "material.h"

namespace CGFF {
    namespace MeshFactory {


		QSharedPointer<Mesh> CreateQuad(float x, float y, float width, float height, QSharedPointer<MaterialInstance> material);

		QSharedPointer<Mesh> CreateQuad(const QVector2D& position, const QVector2D& size, QSharedPointer<MaterialInstance> material);

		QSharedPointer<Mesh> CreateCube(float size, QSharedPointer<MaterialInstance> material);

		QSharedPointer<Mesh> CreateDebugCube(float size, const QVector4D& color, QSharedPointer<MaterialInstance> material);

		QSharedPointer<Mesh> CreateSkyCube(QSharedPointer<MaterialInstance> material);

		QSharedPointer<Mesh> CreatePlane(float width, float height, const QVector3D& normal, QSharedPointer<MaterialInstance> material);

		QSharedPointer<Mesh> CreateDebugPlane(float width, float height, const QVector3D& normal, const QVector4D& color, QSharedPointer<MaterialInstance> material);

		QSharedPointer<Mesh> CreateLine(const QVector3D& start, const QVector3D& end, const QVector4D& color, QSharedPointer<MaterialInstance> material);

    }
}

#endif
