#ifndef MAYA_CAMERA_H
#define MAYA_CAMERA_H

#include "camera.h"

namespace CGFF {

    class MayaCamera : public Camera
    {
    public:
        MayaCamera(const QMatrix4x4& projectionMatrix);
        void update() override;

    private:
        void mousePan(const QVector2D& delta);
        void mouseRotate(const QVector2D& delta);
        void mouseZoom(float delta);

        // TODO: Move up to camera class
        QVector3D getUpDirection();
        QVector3D getRightDirection();
        QVector3D getForwardDirection();

        QVector3D getPosition();
        QQuaternion getOrientation();

    private:
        bool m_panning, m_rotating;
        QVector2D m_initialMousePosition;
        QVector3D m_initialFocalPoint, m_initialRotation;

        float m_distance;
        float m_panSpeed, m_rotationSpeed, m_zoomSpeed;

        float m_pitch, m_yaw;
    };

}

#endif
