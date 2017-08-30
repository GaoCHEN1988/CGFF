#ifndef CGFF_TRANSFORM_COMPONENTS_H
#define CGFF_TRANSFORM_COMPONENTS_H

#include "maths/qtmaths.h"
#include "component.h"

namespace CGFF {

    class TransformComponent : public Component
    {
    public:
        TransformComponent(const QMatrix4x4& transform);

        static ComponentType* getStaticType()
        {
            static ComponentType type({ "Transform" });
            return &type;
        }

        inline virtual ComponentType* getType() const override { return getStaticType(); }

    public:
        QMatrix4x4 transform;
    };
}
#endif