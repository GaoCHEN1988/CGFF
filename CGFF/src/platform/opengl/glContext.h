#ifndef CGFF_GL_CONTEXT_H
#define CGFF_GL_CONTEXT_H

#include "graphic/api/context.h"
#include <QOpenGLContext>
#include <QOpenGLWidget>

namespace CGFF {

    class GLContext : public Context
    {
    public:
        GLContext(QWindow *parent = Q_NULLPTR);

        void present();

        inline static QSharedPointer<GLContext> get() { return qSharedPointerCast<GLContext>(s_context); }

	private:
		QOpenGLContext m_glContext;
		QWindow * m_parent;
    };

}

#endif
