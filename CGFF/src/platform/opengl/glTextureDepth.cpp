#include "glTextureDepth.h"

namespace CGFF {

	GLTextureDepth::GLTextureDepth(int width, int height)
		: m_width(width)
		, m_height(height)
		, m_glTexture(QOpenGLTexture::Target2D)
	{
		init();
	}

	void GLTextureDepth::bind(uint slot)
	{
		m_glTexture.bind(slot);
	}

	void GLTextureDepth::unBind(uint slot)
	{
		m_glTexture.release(slot);
	}

	void GLTextureDepth::init()
	{
		QImage white(m_width, m_height, QImage::Format_RGBA8888);
		white.fill(Qt::white);

		//Need to test, not completed yet
		m_glTexture.create();
		m_glTexture.setSize(white.width(), white.height(), white.depth());
		m_glTexture.setFormat(QOpenGLTexture::D16);
		m_glTexture.setDepthStencilMode(QOpenGLTexture::DepthMode);
		m_glTexture.allocateStorage();

		

		m_glTexture.setData(0, 0, QOpenGLTexture::Depth, QOpenGLTexture::UInt16, (const void*)white.constBits());
		m_glTexture.generateMipMaps();
		m_glTexture.setWrapMode(m_parameters.gl_wrap);
		m_glTexture.setMinMagFilters(m_parameters.gl_filter, m_parameters.gl_filter);
	}
}