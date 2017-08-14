#include "glRenderer.h"

namespace CGFF {


	GLRenderer::GLRenderer()
	{
		m_glContext = GLContext::get();
	}


	void GLRenderer::initInternal() 
	{
		setDepthTesting(true);
		setBlend(true);
		setBlendFunction(RendererBlendFunction::SOURCE_ALPHA, RendererBlendFunction::ONE_MINUS_SOURCE_ALPHA);

		// Move to API independent layer
		GL->glEnable(GL_CULL_FACE);
		GL->glFrontFace(GL_CCW);
		GL->glCullFace(GL_BACK);

		m_rendererTitle = "OpenGL";
	}

	void GLRenderer::clearInternal(uint buffer) 
	{
		GL->glClear(rendererBufferToGL(buffer));
	}

	void GLRenderer::presentInternal() 
	{
		m_glContext->present();
	}

	void GLRenderer::setDepthTestingInternal(bool enabled) 
	{
		if (enabled)
		{
			GL->glEnable(GL_DEPTH_TEST);
		}
		else
		{
			GL->glDisable(GL_DEPTH_TEST);
		}
	}

	void GLRenderer::setBlendInternal(bool enabled) 
	{
		if (enabled)
		{
			GL->glEnable(GL_BLEND);
		}
		else
		{
			GL->glDisable(GL_BLEND);
		}
	}

	void GLRenderer::setViewportInternal(uint x, uint y, uint width, uint height) 
	{
		GL->glViewport(x, y, width, height);
	}

	void GLRenderer::setBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination) 
	{
		GL->glBlendFunc(rendererBlendFunctionToGL(source), rendererBlendFunctionToGL(destination));
	}

	void GLRenderer::setBlendEquationInternal(RendererBlendFunction blendEquation) 
	{
		qFatal("Blend Equation Not Implemented");
	}

	QString GLRenderer::getTitleInternal() 
	{
		return m_rendererTitle;
	}

	uint GLRenderer::rendererBufferToGL(uint buffer)
	{
		uint result = 0;
		if (buffer & RENDERER_BUFFER_COLOR)
			result |= GL_COLOR_BUFFER_BIT;
		if (buffer & RENDERER_BUFFER_DEPTH)
			result |= GL_DEPTH_BUFFER_BIT;
		if (buffer & RENDERER_BUFFER_STENCIL)
			result |= GL_STENCIL_BUFFER_BIT;
		return result;
	}

	uint GLRenderer::rendererBlendFunctionToGL(RendererBlendFunction function)
	{
		switch (function)
		{
		case RendererBlendFunction::ZERO:						
			return GL_ZERO;
		case RendererBlendFunction::ONE:						
			return GL_ONE;
		case RendererBlendFunction::SOURCE_ALPHA:				
			return GL_SRC_ALPHA;
		case RendererBlendFunction::DESTINATION_ALPHA:			
			return GL_DST_ALPHA;
		case RendererBlendFunction::ONE_MINUS_SOURCE_ALPHA:		
			return GL_ONE_MINUS_SRC_ALPHA;
		}
		return 0;
	}

}