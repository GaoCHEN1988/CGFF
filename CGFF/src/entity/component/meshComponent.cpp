#include "meshComponent.h"

namespace CGFF {

    MeshComponent::MeshComponent(const QSharedPointer<Mesh>&  mesh)
        : mesh(mesh)
    {
    }
}