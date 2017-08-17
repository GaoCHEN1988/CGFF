#include "fpsCamera.h"
#include "utils/qtopengl.h"

namespace CGFF {

    FPSCamera::FPSCamera(const QMatrix4x4& projectionMatrix)
        : Camera(projectionMatrix)
        , m_mouseSensitivity(0.002f)
        , m_speed(0.4f)
        , m_sprintSpeed(m_speed * 4.0f)
        , m_mouseWasGrabbed(false)
    {
        m_position = QVector3D(0.0f, 25.0f, -25.0f);
        m_rotation = QVector3D(90.0f, 0.0f, 0.0f);
        m_yaw = 2.4f;
        m_pitch = 0.7f;
    }
    void FPSCamera::focus()
    {
    }
    void FPSCamera::update()
    {
        QSize windowSize = g_openglWidgetSize;
        QVector2D windowCenter = QVector2D((float)(windowSize.width() / 2.0f), (float)(windowSize.height() / 2.0f));

        //if (Input::IsMouseButtonPressed(SP_MOUSE_RIGHT))
        //{
        //    if (!Input::GetInputManager()->IsMouseGrabbed())
        //    {
        //        Input::GetInputManager()->SetMouseGrabbed(true);
        //        Input::GetInputManager()->SetMouseCursor(SP_NO_CURSOR);
        //    }
        //}

        //if (Input::GetInputManager()->IsMouseGrabbed())
        //{
        //    QVector2D mouse = Input::GetInputManager()->GetMousePosition();
        //    mouse.x -= windowCenter.x;
        //    mouse.y -= windowCenter.y;
        //    SP_WARN(mouse);
        //    if (m_MouseWasGrabbed)
        //    {
        //        m_Yaw += mouse.x * m_MouseSensitivity;
        //        m_Pitch += mouse.y * m_MouseSensitivity;
        //    }
        //    m_MouseWasGrabbed = true;
        //    Input::GetInputManager()->SetMousePosition(windowCenter);

        //    Quaternion orientation = GetOrientation();
        //    m_Rotation = orientation.ToEulerAngles() * (180.0f / SP_PI);

        //    vec3 forward = GetForwardDirection(orientation);
        //    vec3 right = GetRightDirection(orientation);
        //    vec3 up = vec3::YAxis();
        //    float speed = Input::IsKeyPressed(SP_KEY_SHIFT) ? m_SprintSpeed : m_Speed;
        //    if (Input::IsKeyPressed(SP_KEY_W))
        //        m_Position += forward * speed;
        //    else if (Input::IsKeyPressed(SP_KEY_S))
        //        m_Position -= forward * speed;

        //    if (Input::IsKeyPressed(SP_KEY_A))
        //        m_Position -= right * speed;
        //    else if (Input::IsKeyPressed(SP_KEY_D))
        //        m_Position += right * speed;

        //    if (Input::IsKeyPressed(SP_KEY_SPACE))
        //        m_Position += up * speed;
        //    if (Input::IsKeyPressed(SP_KEY_CONTROL))
        //        m_Position -= up * speed;

        //    mat4 rotation = mat4::Rotate(orientation.Conjugate());
        //    mat4 translation = mat4::Translate(-m_Position);
        //    m_ViewMatrix = rotation * translation;
        //}
    }

    QQuaternion FPSCamera::getOrientation() const
    {
        return QQuaternion(cos(-m_yaw*0.5), 0.0f, sin(-m_yaw*0.5), 0.0f)*QQuaternion(cos(-m_pitch*0.5), sin(-m_pitch*0.5), 0.0f, 0.0f);
    }

    QVector3D FPSCamera::getForwardDirection(const QQuaternion& orientation) const
    {
        return getOrientation().rotatedVector(-QVector3D(0.0f, 0.0f, 1.0f)); //Z axis
    }

    QVector3D FPSCamera::getUpDirection(const QQuaternion& orientation) const
    {
        return getOrientation().rotatedVector(QVector3D(0.0f, 1.0f, 0.0f)); //Y axis
    }

    QVector3D FPSCamera::getRightDirection(const QQuaternion& orientation) const
    {
        return getOrientation().rotatedVector(QVector3D(1.0f, 0.0f, 0.0f)); //X axis
    }

}
