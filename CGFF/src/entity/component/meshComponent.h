#ifndef CGFF_MESH_COMPONENTS_H
#define CGFF_MESH_COMPONENTS_H

#include "component.h"
#include "graphic/mesh.h"

namespace CGFF {
    class MeshComponent : public Component
    {
    public:
        MeshComponent(const QSharedPointer<Mesh>& mesh);

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