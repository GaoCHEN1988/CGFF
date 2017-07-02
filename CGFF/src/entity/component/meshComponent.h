#ifndef MESH_COMPONENTS_H
#define MESH_COMPONENTS_H

#include "component.h"
#include "graphic/mesh.h"

namespace CGFF {
    class MeshComponent : public Component
    {
    public:
        MeshComponent(QSharedPointer<Mesh> mesh);

        static ComponentType* getStaticType()
        {
            static ComponentType type({ "Mesh" });
            return &type;
        }

        inline virtual ComponentType* getType() const override { return getStaticType(); }

    public:
        QSharedPointer<Mesh> mesh;
    };


}
#endif