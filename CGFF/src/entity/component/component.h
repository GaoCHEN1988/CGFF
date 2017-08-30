#ifndef CGFF_COMPONENT_H
#define CGFF_COMPONENT_H

#include <QString>
#include <QSharedPointer>
namespace CGFF {

    struct ComponentType
    {
        QString name;
    };

    class Entity;

    class Component
    {
    protected:
        QSharedPointer<Entity> m_entity;
    public:
        virtual QSharedPointer<Entity> getEntity() { return m_entity; }
        virtual ComponentType* getType() const { return nullptr; }
    };
}
#endif