#ifndef CGFF_GL_RENDERER_H
#define CGFF_GL_RENDERER_H

#include "graphic/renderer/renderer.h"
#include "glContext.h"

namespace CGFF {

	class GLRenderer : public Renderer
	{
	public:
		GLRenderer();

	protected:
		void initInternal() override;

		void clearInternal(uint buffer) override;
		void presentInternal() override;

		void setDepthTestingInternal(bool enabled) override;
		void setBlendInternal(bool enabled) override;
		void setViewportInternal(uint x, uint y, uint width, uint height) override;

		void setBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination) override;
		void setBlendEquationInternal(RendererBlendFunction blendEquation) override;

	    QString getTitleInternal() override;
	public:
		static uint rendererBufferToGL(uint buffer);
		static uint rendererBlendFunctionToGL(RendererBlendFunction function);

	private:
		QSharedPointer<GLContext> m_glContext;
		QString m_rendererTitle;
	};

}

#endif