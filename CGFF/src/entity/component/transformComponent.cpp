#include "transformComponent.h"

namespace CGFF {
    TransformComponent::TransformComponent(const QMatrix4x4& transform)
        : transform(transform)
    {
    }

}