#ifndef CGFF_MODEL_OBJECT_H
#define CGFF_MODEL_OBJECT_H

#include "entity.h"
#include "graphic/model.h"

namespace CGFF {
    class ModelObject
    {
    public:
        explicit ModelObject(const QString& name = "", const QSharedPointer<Model>& model = nullptr);
        ~ModelObject();

        void addEntity(const QString& name, const QSharedPointer<Entity>& entity);
        void transform(const QMatrix4x4& transform);
        inline const QMap<QString, QSharedPointer<Entity>>& getEntities() { return m_entities;}
        inline void setName(const QString& name) { m_name = name; }
        inline QString getName(const QString& name) { return m_name; }

    private:
        void load(const QSharedPointer<Model>& model);
    private:
        QMap<QString, QSharedPointer<Entity>> m_entities;
        QString m_name;
        int m_entityCount;
        QMatrix4x4 m_modelTransform;
    };
}

#endif
