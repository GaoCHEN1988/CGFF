#include "entity.h"

namespace CGFF {

    Entity::Entity()
    {
    }

	Entity::Entity(QSharedPointer<Mesh> mesh, QMatrix4x4 transform )
	{
		addComponent(QSharedPointer<MeshComponent>(new MeshComponent(mesh)));
		addComponent(QSharedPointer<TransformComponent>(new TransformComponent(transform)));
	}

    void Entity::addComponent(QSharedPointer<Component> component)
    {
        m_components.append(component);
    }

}