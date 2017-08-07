#ifndef FPS_CAMERA_H
#define FPS_CAMERA_H

#include "camera.h"

namespace CGFF {

    class FPSCamera : public Camera
    {
    public:
        FPSCamera(const QMatrix4x4& projectionMatrix);
        void focus() override;
        void update() override;
    private:
        QQuaternion getOrientation() const;
        QVector3D getForwardDirection(const QQuaternion& orientation) const;
        QVector3D getUpDirection(const QQuaternion& orientation) const;
        QVector3D getRightDirection(const QQuaternion& orientation) const;

    private:
        float m_mouseSensitivity;
        float m_speed, m_sprintSpeed;
        float m_pitch, m_yaw;
        bool m_mouseWasGrabbed;
    };


}

#endif