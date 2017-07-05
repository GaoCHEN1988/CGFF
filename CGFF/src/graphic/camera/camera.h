#ifndef CAMERA_H
#define CAMERA_H

#include "maths/qtmaths.h"
#include <QMouseEvent>

namespace CGFF {

    class Camera
    {
    public:
        Camera(const QMatrix4x4& projectionMatrix);
        ~Camera();

        virtual void update() { }
        virtual void mousePressEvent(QMouseEvent * event) {}
        virtual void mouseMoveEvent(QMouseEvent * event) {}
        virtual void resize(int width, int height) {};

        inline const QVector3D& getPosition() const { return m_position; }
        inline void SetPosition(const QVector3D& position) { m_position = position; }

        inline const QVector3D& getRotation() const { return m_rotation; }
        inline void setRotation(const QVector3D& rotation) { m_rotation = rotation; }

        inline const QMatrix4x4& getProjectionMatrix() const { return m_projectionMatrix; }
        inline void setProjectionMatrix(const QMatrix4x4& projectionMatrix) { m_projectionMatrix = projectionMatrix; }

        inline void translate(const QVector3D& translation) { m_position += translation; }
        inline void rotate(const QVector3D& rotation) { m_rotation += rotation; }

        inline void translate(float x, float y, float z) { m_position += QVector3D(x, y, z); }
        inline void rotate(float x, float y, float z) { m_rotation += QVector3D(x, y, z); }

        inline const QVector3D& getFocalPoint() const { return m_focalPoint; }

        inline const QMatrix4x4& getViewMatrix() { return m_viewMatrix; }

    protected:
        QMatrix4x4 m_projectionMatrix, m_viewMatrix;
        QVector3D m_position, m_rotation, m_focalPoint;
    };

}
#endif

