#include "mayaCamera.h"

namespace CGFF {

    MayaCamera::MayaCamera(const QMatrix4x4& projectionMatrix)
        : Camera(projectionMatrix)
    {
        // Sensible defaults
        m_panSpeed = 0.0015f;
        m_rotationSpeed = 0.002f;
        m_zoomSpeed = 0.2f;

        m_position = QVector3D(0.0f, 25.0f, -25.0f);
        m_rotation = QVector3D(90.0f, 0.0f, 0.0f);

        m_focalPoint = QVector3D(0.0f, 0.0f, 0.0f);
        m_distance = m_position.distanceToPoint(m_focalPoint);

        m_yaw = 3.0f * float(M_PI) / 4.0f;
        m_pitch = float(M_PI) / 4.0f;
    }

    void MayaCamera::update()
    {
        //Window* window = Window::GetWindowClass(nullptr);

        //if (window->IsKeyPressed(VK_ALT))
        //{
        //    const vec2& mouse = window->GetMousePosition();
        //    vec2 delta = mouse - m_InitialMousePosition;
        //    m_InitialMousePosition = mouse;

        //    if (window->IsMouseButtonPressed(SP_MOUSE_MIDDLE))
        //        MousePan(delta);
        //    else if (window->IsMouseButtonPressed(SP_MOUSE_LEFT))
        //        MouseRotate(delta);
        //    else if (window->IsMouseButtonPressed(SP_MOUSE_RIGHT))
        //        MouseZoom(delta.y);

        //}

        // MouseZoom(window->GetMouseScrollPosition().y);

        //Need to test
        QMatrix4x4 rotate_mat;
        rotate_mat.rotate(getOrientation().conjugate());
        m_viewMatrix = rotate_mat;

        QMatrix4x4 translate_mat;
        translate_mat.translate(-getPosition());
        m_viewMatrix *= translate_mat;
    }

    void MayaCamera::mousePan(const QVector2D& delta)
    {
        m_focalPoint += -getRightDirection() * delta.x() * m_panSpeed * m_distance;
        m_focalPoint += getUpDirection() * delta.y() * m_panSpeed * m_distance;
    }

    void MayaCamera::mouseRotate(const QVector2D& delta)
    {
        float yawSign = getUpDirection().y() < 0 ? -1.0f : 1.0f;
        m_yaw += yawSign * delta.x() * m_rotationSpeed;
        m_pitch += delta.y() * m_rotationSpeed;
    }

    void MayaCamera::mouseZoom(float delta)
    {
        m_distance -= delta * m_zoomSpeed;
    }

    QVector3D MayaCamera::getUpDirection()
    {
        return getOrientation().rotatedVector(QVector3D(0.0f, 1.0f, 0.0f)); //Y axis
    }

    QVector3D MayaCamera::getRightDirection()
    {
        return getOrientation().rotatedVector(QVector3D(1.0f, 0.0f, 0.0f)); //X axis
    }

    QVector3D MayaCamera::getForwardDirection()
    {
        return getOrientation().rotatedVector(-QVector3D(0.0f, 0.0f, 1.0f)); //Z axis
    }

    QVector3D MayaCamera::getPosition()
    {
        return m_focalPoint - m_distance * getForwardDirection();
    }

    QQuaternion MayaCamera::getOrientation()
    {
        return QQuaternion::fromEulerAngles(-m_pitch, -m_yaw, 0.0f);
    }
}