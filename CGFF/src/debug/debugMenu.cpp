#include "debugMenu.h"
#include <QPainter>

namespace CGFF {

    DebugMenu * DebugMenu::m_instance = nullptr;

    DebugMenu::DebugMenu()
        : m_visible(false)
    {

    }

    void DebugMenu::add(QString name)
    {
        m_instance->m_debugMenuItems.append({ name });
    }

    bool DebugMenu::isVisible()
    {
        return m_instance->m_visible;
    }

    void DebugMenu::setVisible(bool visible)
    {
        m_instance->m_visible = visible;
    }

    void DebugMenu::render(QSharedPointer<Renderer2D>& renderer)
    {
        int width = 300;
        int height = 40;
        float yOffset = 0;
        float y = 10.0f;

        for (DebugMenuItem& item : m_instance->m_debugMenuItems)
        {
            /*QImage textimg(width, height, QImage::Format_ARGB32);
            {
                QPainter painter(&textimg);
                textimg.fill(Qt::transparent);
                painter.setBrush(QColor(247, 247, 247, 247));
                painter.setPen(QColor(247, 247, 247, 247));
                painter.setFont(QFont("Sans", 20));
                painter.drawText(0, height, item.name);
            }

            renderer->drawString(QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(textimg.mirrored())), QVector3D(2, y+ yOffset, 0), width, height, QVector4D(0.967, 0.967, 0.967, 0.967));
*/
            renderer->drawString(item.name, QVector3D(2, y + yOffset, 0), width, height, QVector4D(0.967, 0.967, 0.967, 0.967));
            renderer->fillRect(2, y + yOffset, width, height, QVector4D(0.5, 0.5, 0.5, 0.5));

            yOffset += 45.0f;
        }
    }

}