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

        inline QMatrix4x4 getTransform()
        {
            return m_parentTransform * m_transform;
        }
        inline QMatrix4x4 setTransform(const QMatrix4x4& transform)
        {
            return m_transform = transform;
        }

        inline QMatrix4x4 setParentTransform(const QMatrix4x4& transform)
        {
            return m_parentTransform = transform;
        }

    public:
        QMatrix4x4 m_transform;
        QMatrix4x4 m_parentTransform;
    };
}
#endif