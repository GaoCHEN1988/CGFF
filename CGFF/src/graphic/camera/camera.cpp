#include "camera.h"

namespace CGFF {

    Camera::Camera(const QMatrix4x4& projectionMatrix)
        : m_projectionMatrix(projectionMatrix)
    {
        m_viewMatrix.setToIdentity();
    }


    Camera::~Camera()
    {
    }

}