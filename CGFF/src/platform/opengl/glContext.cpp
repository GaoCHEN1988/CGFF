#include "glContext.h"

namespace CGFF {

	GLContext::GLContext(QWindow *parent)
		: m_glContext(parent)
		, m_parent(parent)
	{
		//test
		QSurfaceFormat qFormat = parent->requestedFormat();
		qFormat.setProfile(QSurfaceFormat::CoreProfile);
		qFormat.setVersion(4, 4);
		m_glContext.setFormat(qFormat);

		// initialize OpenGL functions
		CGFF::GL = m_glContext.versionFunctions<QOpenGLFunctions_4_4_Core>();
		CGFF::GL->initializeOpenGLFunctions();
	}

	void GLContext::present()
	{
		m_glContext.swapBuffers(m_parent);
	}

}