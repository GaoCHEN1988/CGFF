#include "glFramebufferDepth.h"

namespace CGFF {


	GLFramebufferDepth::GLFramebufferDepth(int width, int height)
		: m_width(width)
		, m_height(height)
	{
		init();
	}

	GLFramebufferDepth::~GLFramebufferDepth()
	{
		GL->glDeleteFramebuffers(1, &m_framebufferID);
	}

	void GLFramebufferDepth::bind()
	{
		GL->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		GL->glViewport(0, 0, m_width, m_height);
	}

	void GLFramebufferDepth::unBind()
	{
		GL->glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void GLFramebufferDepth::clear()
	{
		GL->glClear(GL_DEPTH_BUFFER_BIT);
	}

	int GLFramebufferDepth::getWidth() const 
	{
		return m_width;
	}

	int GLFramebufferDepth::getHeight() const 
	{
		return m_height;
	}

	QSharedPointer<Texture> GLFramebufferDepth::getTexture() const 
	{
		return m_glTexture;
	}

	void GLFramebufferDepth::init() 
	{
		m_glTexture = QSharedPointer<GLTextureDepth>(new GLTextureDepth(m_width, m_height));

		GL->glGenFramebuffers(1, &m_framebufferID);
		GL->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

		GL->glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_glTexture->getID(), 0);
		GL->glDrawBuffer(GL_NONE);
		Q_ASSERT(GL->glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

		GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}