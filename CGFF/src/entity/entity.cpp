#include "entity.h"

namespace CGFF {

    Entity::Entity()
    {
    }

	Entity::Entity(QSharedPointer<Mesh> mesh, const QMatrix4x4& transform )
	{
		addComponent(QSharedPointer<MeshComponent>(new MeshComponent(mesh)));
		addComponent(QSharedPointer<TransformComponent>(new TransformComponent(transform)));
	}

	Entity::Entity(QSharedPointer<Sprite> sprite, const QMatrix4x4& transform)
	{
		addComponent(QSharedPointer<SpriteComponent>(new SpriteComponent(sprite)));
		addComponent(QSharedPointer<TransformComponent>(new TransformComponent(transform)));
	}

    void Entity::addComponent(QSharedPointer<Component> component)
    {
        m_components.append(component);
    }

}