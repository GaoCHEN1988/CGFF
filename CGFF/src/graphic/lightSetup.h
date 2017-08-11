#ifndef CGFF_LIGHT_SETUP_H
#define CGFF_LIGHT_SETUP_H

#include "light.h"

namespace CGFF {

    class LightSetup
    {
    public:
        LightSetup();
        ~LightSetup();

        QSharedPointer<Light> add(QSharedPointer<Light> light);
        void remove(QSharedPointer<Light> light);

        inline const QVector<QSharedPointer<Light>>& getLights() const { return m_lights; }

    private:
        QVector<QSharedPointer<Light>> m_lights;
    };
}

#endif