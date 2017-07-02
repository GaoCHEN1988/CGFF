#include "entity.h"

namespace CGFF {

    Entity::Entity()
    {
    }

    void Entity::addComponent(QSharedPointer<Component> component)
    {
        m_components.append(component);
    }

}