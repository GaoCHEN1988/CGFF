#include "mayaCamera.h"
#include <QCursor>

namespace CGFF {

    MayaCamera::MayaCamera(const QMatrix4x4& projectionMatrix)
        : Camera(projectionMatrix)
		, m_isLeftPressed(false)
		, m_isRightPressed(false)
		, m_isMiddlePressed(false)
    {
        // Sensible defaults
        m_panSpeed = 0.001f;
        m_rotationSpeed = 0.001f;
        m_zoomSpeed = 0.1f;

		m_position = QVector3D(0.0f, 0.0f, -25.0f);
		//m_position = QVector3D(0.0f, 0.0f, 0.0f);
        m_rotation = QVector3D(90.0f, 0.0f, 0.0f);

        m_focalPoint = QVector3D(0.0f, 0.0f, 0.0f);
        m_distance = m_position.distanceToPoint(m_focalPoint);

        m_yaw = 3.0f * float(M_PI) / 4.0f;
        m_pitch = float(M_PI) / 4.0f;
    }

    void MayaCamera::update()
    {
		QVector2D mouse = QVector2D(QCursor::pos());
        QVector2D delta = mouse - m_initialMousePosition;
        m_initialMousePosition = mouse;

        if (m_isMiddlePressed)
            mousePan(delta);
        else if (m_isLeftPressed)
            mouseRotate(delta);
        else if (m_isRightPressed)
            mouseZoom(delta.y());

        // MouseZoom(window->GetMouseScrollPosition().y);
		m_position = calculatePosition();

        //Need to test  
        QQuaternion orientation = getOrientation();

		//test!!!
        m_rotation = orientation.toEulerAngles()* (180.0f / M_PI);

        QMatrix4x4 translate_mat;
        translate_mat.translate(QVector3D(0, 0, 1));

		QMatrix4x4 translate_mat2;
		translate_mat2.translate(-m_position);

		QMatrix4x4 rotate_mat;
		rotate_mat.rotate(orientation.conjugate());

		m_viewMatrix = translate_mat * rotate_mat * translate_mat2;
    }

	void MayaCamera::focus()
	{
		//Input::GetInputManager()->SetMouseCursor(1);
	}

    void MayaCamera::mousePressEvent(QMouseEvent * event)
    {
        if (event->buttons() == Qt::LeftButton)
        {
            m_isLeftPressed = true;
        }
        else 
        {
            m_isLeftPressed = false;       
        }       

        if (event->buttons() == Qt::RightButton)
        {
            m_isRightPressed = true;
        }
        else 
        {
            m_isRightPressed = false;
        }
            
        if (event->buttons() == Qt::MidButton)
        {
            m_isMiddlePressed = true;
        }
        else
        {
            m_isMiddlePressed = false;
        }
     
    }

    void MayaCamera::mouseMoveEvent(QMouseEvent * event)
    {
    }

    void MayaCamera::resize(int width, int height)
    {
        m_projectionMatrix.setToIdentity();
        m_projectionMatrix.perspective(65.0f, float(width) / float(height), 0.1f, 1000.0f);
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

		if (m_distance < 1.0f)
		{
			m_focalPoint += getForwardDirection();
			m_distance = 1.0f;
		}

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

    QVector3D MayaCamera::calculatePosition()
    {
        return m_focalPoint - m_distance * getForwardDirection();
    }

    QQuaternion MayaCamera::getOrientation()
    {
        //return QQuaternion::fromEulerAngles(-m_pitch, -m_yaw, 0.0f);
        //return QQuaternion::fromAxisAndAngle(0.0, 1.0f, 0.0f, -m_yaw*0.5)*QQuaternion::fromAxisAndAngle(1.0, 0.0f, 0.0f, -m_pitch*0.5);
        return QQuaternion(cos(-m_yaw*0.5), 0.0f, sin(-m_yaw*0.5), 0.0f)*QQuaternion(cos(-m_pitch*0.5), sin(-m_pitch*0.5), 0.0f, 0.0f);
    }
}