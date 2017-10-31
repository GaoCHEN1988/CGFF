#include "lightSetup.h"

namespace CGFF {

    LightSetup::LightSetup()
    {

    }

    LightSetup::~LightSetup()
    {
        m_lights.clear();
        m_lightEntities.clear();
    }

    void LightSetup::add(const Light& light, const QSharedPointer<Entity>& lightEntity)
    {
        m_lights.append(light);
        m_lightEntities.append(lightEntity);
    }

    void LightSetup::remove(int i)
    {
        if(!m_lights.empty())
            m_lights.remove(i);

        if (!m_lightEntities.empty())
            m_lightEntities.remove(i);
    }

}