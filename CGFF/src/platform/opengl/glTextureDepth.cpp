#include "glTextureDepth.h"
#include "utils/qtopengl.h"

namespace CGFF {

	GLTextureDepth::GLTextureDepth(int width, int height)
		: m_width(width)
		, m_height(height)
		, m_glTexture(QOpenGLTexture::Target2D)
        //, m_handle(0)
	{
		init();
	}

	void GLTextureDepth::bind(uint slot)
	{
        m_glTexture.bind(slot);
        //GL->glActiveTexture(GL_TEXTURE0 + slot);
        //GL->glBindTexture(GL_TEXTURE_2D, m_handle);
	}

	void GLTextureDepth::unBind(uint slot)
	{
		m_glTexture.release(slot);
        //GL->glActiveTexture(GL_TEXTURE0 + slot);
        //GL->glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLTextureDepth::init()
	{
		QImage white(m_width, m_height, QImage::Format_RGBA8888);

		//Need to test, not completed yet
		m_glTexture.create();
		m_glTexture.setSize(m_width, m_height);
		m_glTexture.setFormat(QOpenGLTexture::D16);
		m_glTexture.setDepthStencilMode(QOpenGLTexture::DepthMode);
		m_glTexture.allocateStorage();

		m_glTexture.setData(0, 0, QOpenGLTexture::Depth, QOpenGLTexture::Float32, (const void*)white.constBits());
		m_glTexture.setWrapMode(QOpenGLTexture::WrapMode::ClampToBorder);
		m_glTexture.setMinMagFilters(QOpenGLTexture::Filter::Nearest, QOpenGLTexture::Filter::Nearest);

        ////For test
        //GL->glGenTextures(1, &m_handle);
        //GL->glBindTexture(GL_TEXTURE_2D, m_handle);
        //GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        //GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        ////GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        ////GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        ////GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        ////GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        ////GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
        ////GL->glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        //GL->glBindTexture(GL_TEXTURE_2D, 0);
	}
}