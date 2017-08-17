#ifndef ENTITY_H
#define ENTITY_H

#include "component/components.h"
#include <QVector>

namespace CGFF {

    class Entity
    {
    public:
        Entity();
		Entity(QSharedPointer<Mesh> mesh, QMatrix4x4 transform = QMatrix4x4());

        void addComponent(QSharedPointer<Component> component);

        template <typename T>
        const T* getComponent() const
        {
            return getComponentInternal<T>();
        }

        template <typename T>
        T* getComponent()
        {
            return (T*)getComponentInternal<T>();
        }
    private:
        template <typename T>
        const T* getComponentInternal() const
        {
            ComponentType* type = T::getStaticType();
            for (auto x : m_components)
            {
                if (x->getType() == type)
                    return (const T*)x.data();
            }
            return nullptr;
        }

    protected:
        QVector<QSharedPointer<Component> > m_components;
    };


}
#endif
