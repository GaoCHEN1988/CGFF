#include "lightSetup.h"

namespace CGFF {

    LightSetup::LightSetup()
    {

    }

    LightSetup::~LightSetup()
    {
    }

    QSharedPointer<Light> LightSetup::add(QSharedPointer<Light> light)
    {
        m_lights.append(light);
        return light;
    }

    void LightSetup::remove(QSharedPointer<Light> light)
    {
        for (uint i = 0; i < m_lights.size(); i++)
        {
            if (m_lights[i] == light)
            {
                m_lights.remove(i);
                break;
            }
        }
    }

}