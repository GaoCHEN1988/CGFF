#include "modelObject.h"

namespace CGFF {
    ModelObject::ModelObject(const QString& name, const QSharedPointer<Model>& model)
        : m_name(name)
        , m_entityCount(0)
        , m_modelTransform()
    {
        if (!model.isNull())
            load(model);
    }
    ModelObject::~ModelObject()
    {}

    void ModelObject::addEntity(const QString& name, const QSharedPointer<Entity>& entity)
    {
        m_entities.insert(name, entity);
    }

    void ModelObject::transform(const QMatrix4x4& transform)
    {
        for (QSharedPointer<Entity>& entity : m_entities)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            transComponent->setParentTransform(transform);
        }
    }

    void ModelObject::load(const QSharedPointer<Model>& model)
    {
        for (const QSharedPointer<Mesh>& mesh : model->getMeshes())
        {
            m_entityCount++;
            QSharedPointer<CGFF::Entity> objectEntity =
                QSharedPointer<Entity>(new Entity(mesh));

            QString entityName = m_name + "_entity" + QString::number(m_entityCount);
            addEntity(entityName, objectEntity);
        }
    }
}