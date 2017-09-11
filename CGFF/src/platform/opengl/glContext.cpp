#include "glContext.h"

namespace CGFF {

	GLContext::GLContext(QWindow *parent)
		: m_glContext(new QOpenGLContext(parent))
		, m_parent(parent)
	{
		//test
		QSurfaceFormat qFormat = parent->requestedFormat();
		qFormat.setProfile(QSurfaceFormat::CoreProfile);
		qFormat.setVersion(4, 4);
		m_glContext->setFormat(qFormat);
        m_glContext->create();
        m_glContext->makeCurrent(m_parent);
		// initialize OpenGL functions
		CGFF::GL = m_glContext->versionFunctions<QOpenGLFunctions_4_4_Core>();
		CGFF::GL->initializeOpenGLFunctions();
	}

    GLContext::~GLContext()
    {
    }

	void GLContext::present()
	{
        m_glContext->makeCurrent(m_parent);
		m_glContext->swapBuffers(m_parent);
	}

    void GLContext::makeCurrent()
    {
        m_glContext->makeCurrent(m_parent);
    }

	void GLContext::resetContextInternal(QWindow *parent)
	{
		if (!m_glContext)
			return;

		//Test
		m_parent = parent;
		QOpenGLContext* tmpContext = new QOpenGLContext(m_parent);
		tmpContext->setFormat(m_glContext->format());
		tmpContext->setShareContext(m_glContext);
		tmpContext->create();
		tmpContext->makeCurrent(m_parent);
		// initialize OpenGL functions
		CGFF::GL = tmpContext->versionFunctions<QOpenGLFunctions_4_4_Core>();
		CGFF::GL->initializeOpenGLFunctions();
		QOpenGLContext* t = m_glContext;
		m_glContext = tmpContext;
		delete t;
	}
}