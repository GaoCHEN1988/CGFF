#ifndef CGFF_BASE_WINDOW_H
#define CGFF_BASE_WINDOW_H

#include "graphic/layer/layer.h"
#include "graphic/api/context.h"
#include <QWindow>
#include <QTime>

namespace CGFF {
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
		bool event(QEvent *event) Q_DECL_OVERRIDE;

	private:
		QVector<QSharedPointer<CGFF::Layer>> m_layerStack;
		QVector<QSharedPointer<CGFF::Layer>> m_overLayerStack;

		QTime m_time;
		int m_framePerSecond;
		int m_fps_count;
		int m_timer_id;

	protected:
		QWidget * m_parent;
	};
}

#endif
