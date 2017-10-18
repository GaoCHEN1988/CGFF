#include "modelObject.h"

namespace CGFF {
    ModelObject::ModelObject(const QString& name, const QSharedPointer<Model>& model)
        : m_name(name)
    {
        if (!model.isNull())
            load(model);
    }
    ModelObject::~ModelObject()
    {}

    void ModelObject::addEntity(const QSharedPointer<Entity>& entity)
    {
        m_entities.append(entity);
    }

    void ModelObject::transform(const QMatrix4x4& transform)
    {
        for (QSharedPointer<Entity>& entity : m_entities)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            transComponent->transform = transform;
        }
    }

    void ModelObject::load(const QSharedPointer<Model>& model)
    {
        for (const QSharedPointer<Mesh>& mesh : model->getMeshes())
        {
            QSharedPointer<CGFF::Entity> objectEntity =
                QSharedPointer<Entity>(new Entity(mesh));
            addEntity(objectEntity);
        }
    }
}