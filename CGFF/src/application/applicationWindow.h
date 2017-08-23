#pragma once
#include "utils/qtopengl.h"
#include "graphic/layer/layer.h"
#include "Debug/debugLayer.h"
#include "graphic/api/context.h"
#include <QWindow>
#include <QTimer>
#include <QTime>

class ApplicationWindow : public QWindow {
	Q_OBJECT

public:
	ApplicationWindow(QWindow * parent = Q_NULLPTR, CGFF::RenderAPI api = CGFF::RenderAPI::OPENGL);
	virtual ~ApplicationWindow();

	inline static ApplicationWindow* getApplication() { return m_instance; }

	void initialize();
	void render();
	void tick();
	void renderLater();
	void renderNow();

	void pushLayer(QSharedPointer<CGFF::Layer> layer);
	QSharedPointer<CGFF::Layer> popLayer();
	QSharedPointer<CGFF::Layer> popLayer(QSharedPointer<CGFF::Layer> layer);

	void pushOverlay(QSharedPointer<CGFF::Layer> layer);
	QSharedPointer<CGFF::Layer> popOverlay();
	QSharedPointer<CGFF::Layer> popOverlay(QSharedPointer<CGFF::Layer> layer);

	inline int getFPS() { return m_framePerSecond; }

private:
	void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
	void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;
	void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	bool event(QEvent *event) Q_DECL_OVERRIDE;
private:
	QVector<QSharedPointer<CGFF::Layer>> m_layerStack;
	QVector<QSharedPointer<CGFF::Layer>> m_overLayerStack;
	QSharedPointer<CGFF::Layer> m_debugLayer;

	static ApplicationWindow * m_instance;

	QTime m_time;
	int m_framePerSecond;
	int fps_count;
	int timer_id_;
};
