#pragma once

#include "learnOpenglHeader.h"

namespace LearnGL {

        QSharedPointer<CGFF::Mesh> CreateCube(float size, QSharedPointer<CGFF::MaterialInstance> material);

        QSharedPointer<CGFF::Mesh> CreatePlane(float width, float height, const QVector3D& normal, QSharedPointer<CGFF::MaterialInstance> material);
}