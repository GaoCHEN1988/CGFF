#ifndef CGFF_BASE_WINDOW_H
#define CGFF_BASE_WINDOW_H

#include "graphic/layer/layer.h"
#include "graphic/api/context.h"
#include "qtUI/model/resourceModel.h"
#include <QWindow>
#include <QTime>


class BaseWindow : public QWindow
{
    Q_OBJECT

public:

    BaseWindow(QWidget * parent, CGFF::RenderAPI api = CGFF::RenderAPI::OPENGL);
    virtual ~BaseWindow();

    virtual void initialize();
    virtual void update();
    virtual void render();
    virtual void tick();
    virtual void renderLater();
    virtual void renderNow();
    virtual void setupLayers() = 0;
    virtual void clearLayers();
    virtual void setModel(QTUI::ResourceModel * model)
    {
        m_model = model;
    }

    void pushLayer(QSharedPointer<CGFF::Layer> layer);
    QSharedPointer<CGFF::Layer> popLayer();
    QSharedPointer<CGFF::Layer> popLayer(QSharedPointer<CGFF::Layer> layer);
    void pushOverlay(QSharedPointer<CGFF::Layer> layer);
    QSharedPointer<CGFF::Layer> popOverlay();
    QSharedPointer<CGFF::Layer> popOverlay(QSharedPointer<CGFF::Layer> layer);

    inline int getFPS() { return m_framePerSecond; }
    inline void setActive(bool active) { m_isActive = active; }

    public slots:
    void onActivate();
    void onDisactivate();

signals:
    void initilizeSignal();

private:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

    void setUpContext();

private:
    QVector<QSharedPointer<CGFF::Layer>> m_layerStack;
    QVector<QSharedPointer<CGFF::Layer>> m_overLayerStack;

    QTime m_time;
    int m_framePerSecond;
    int m_fps_count;
    int m_timer_id;

    bool m_isActive;

protected:
    QWidget * m_parent;
    QTUI::ResourceModel * m_model;
};

#endif
