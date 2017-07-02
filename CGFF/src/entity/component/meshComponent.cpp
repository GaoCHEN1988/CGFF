#include "meshComponent.h"

namespace CGFF {

    MeshComponent::MeshComponent(QSharedPointer<Mesh> mesh)
        : mesh(mesh)
    {
    }
}