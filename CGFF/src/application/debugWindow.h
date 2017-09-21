#ifndef CGFF_DEBUG_WINDOW_H
#define CGFF_DEBUG_WINDOW_H

#include "baseWindow.h"
#include "debug/debugLayer.h"
#include "Debug/debugLayer3D.h"

namespace CGFF {

	class DebugWindow : public BaseWindow 
	{
		Q_OBJECT

	public:

		DebugWindow(QWidget * parent, CGFF::RenderAPI api = CGFF::RenderAPI::OPENGL);
		virtual ~DebugWindow();

		inline static DebugWindow* getApplication() { return m_instance; }

		public slots:
		void onAddEntity(const QString& name);

	private:
		void setupLayers() override;
	private:
		static DebugWindow * m_instance;

		QSharedPointer<CGFF::DebugLayer3D> m_debug3DLayer;
		QSharedPointer<CGFF::DebugLayer> m_debugLayer;
	};
}

#endif