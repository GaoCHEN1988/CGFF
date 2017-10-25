#ifndef CGFF_LIGHT_SETUP_H
#define CGFF_LIGHT_SETUP_H

#include "light.h"
#include "entity/entity.h"

namespace CGFF {

    class LightSetup
    {
    public:
        LightSetup();
        ~LightSetup();

        QSharedPointer<Light> add(const QSharedPointer<Light>& light, const QSharedPointer<Entity>& lightEntity = nullptr);
        void remove(int i);

        inline const QVector<QSharedPointer<Light>>& getLights() const { return m_lights; }
        inline const QVector<QSharedPointer<Entity>>& getLightEntities() const { return m_lightEntities; }

    private:
        QVector<QSharedPointer<Light>> m_lights;
        QVector<QSharedPointer<Entity>> m_lightEntities;
    };
}

#endif