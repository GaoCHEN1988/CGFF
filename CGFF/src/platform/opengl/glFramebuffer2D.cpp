#include "glFramebuffer2D.h"

namespace CGFF {

	GLFramebuffer2D::GLFramebuffer2D(int width, int height)
		: m_glTexture(nullptr)
		, m_width(width)
		, m_height(height)
        , m_clearColor(0, 0, 0, 0)
	{
		init();
	}

	GLFramebuffer2D::~GLFramebuffer2D()
	{
		GL->glDeleteFramebuffers(1, &m_framebufferHandle);
	}

	void GLFramebuffer2D::bind()
	{
		GL->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle);
		GL->glViewport(0, 0, m_width, m_height);
	}

	void GLFramebuffer2D::unBind()
	{
		GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GLFramebuffer2D::clear()
	{
		GL->glClearColor(m_clearColor.x(), m_clearColor.y(), m_clearColor.z(), m_clearColor.w());
		GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int GLFramebuffer2D::getWidth() const
	{
		return m_width;
	}

	int GLFramebuffer2D::getHeight() const
	{
		return m_height;
	}

    QSize GLFramebuffer2D::getSize() const
    {
        return QSize(m_width, m_height);
    }

	QSharedPointer<Texture> GLFramebuffer2D::getTexture() const
	{
		return m_glTexture;
	}

	void GLFramebuffer2D::setClearColor(const QVector4D& color)
	{
		m_clearColor = color;
	}

	void GLFramebuffer2D::init()
	{
		TextureParameters params;
		m_glTexture = QSharedPointer<GLTexture2D>(new GLTexture2D(m_width, m_height, params));

		GL->glGenFramebuffers(1, &m_framebufferHandle);
		GL->glGenRenderbuffers(1, &m_depthbufferHandle);

		GL->glBindRenderbuffer(GL_RENDERBUFFER, m_depthbufferHandle);
		GL->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, (GLsizei)m_width, (GLsizei)m_height);

		GL->glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle);
		GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glTexture->getID(), 0);
		GL->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbufferHandle);
		GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
}