#include "glTexture2D.h"
#include "glContext.h"
#include "system/fileSystem/vfs.h"

namespace CGFF {

	GLTexture2D::GLTexture2D(int width, int height, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_name("")
		, m_fileName("")
		, m_width(width)
		, m_height(height)
		, m_parameters(parameters)
		, m_loadOptions(loadOptions)
		, m_glTexture(QOpenGLTexture::Target2D)
	{
		load();
	}

	GLTexture2D::GLTexture2D(int width, int height, int color, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_name("")
		, m_fileName("")
		, m_width(width)
		, m_height(height)
		, m_parameters(parameters)
		, m_loadOptions(loadOptions)
		, m_glTexture(QOpenGLTexture::Target2D)
	{
		load(color);
	}

	GLTexture2D::GLTexture2D(const QString& name, const QString& filename, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_name(name)
		, m_fileName("")
		, m_width(1)
		, m_height(1)
		, m_parameters(parameters)
		, m_loadOptions(loadOptions)
		, m_glTexture(QOpenGLTexture::Target2D)
	{
		if (!VFS::get()->resolvePhysicalPath(filename, m_fileName))
			qFatal("Can't load file: ", filename);

		load();
	}

	GLTexture2D::GLTexture2D(const QString& name, const QImage& image, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_name(name)
		, m_fileName("")
		, m_width(image.width())
		, m_height(image.height())
		, m_parameters(parameters)
		, m_loadOptions(loadOptions)
		, m_glTexture(QOpenGLTexture::Target2D)
	{
		load(image);
	}

    GLTexture2D::~GLTexture2D()
    {
    }

	void GLTexture2D::setTexture(GLuint id)
	{
		m_glTexture.bind(id);
	}

	void GLTexture2D::bind(uint slot)
	{
		m_glTexture.bind(slot);
	}

	void GLTexture2D::unBind(uint slot)
	{
		m_glTexture.release(slot);
	}

	void GLTexture2D::load()
	{
		if (!m_fileName.isEmpty())
		{
			QImage texImage;

			//To do: Test tga files
			if (texImage.load(m_fileName))
			{
				m_glTexture.create();
                //m_glTexture.setSize(texImage.width(), texImage.height(), texImage.depth());
                m_glTexture.setSize(texImage.width(), texImage.height(), texImage.depth());
                m_glTexture.setFormat(m_parameters.gl_textureFormat);
				m_glTexture.allocateStorage();
            
                QImage tmp = texImage.convertToFormat(m_parameters.imageFormat);
				tmp = tmp.mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip);
                m_glTexture.setData(0, 0, m_parameters.gl_pixelFormat, m_parameters.gl_pixelType, (const void*)tmp.constBits(), 0);
			}
			else
			{
				qFatal("Can't load image from ", m_fileName);
				return;
			}
		}
        else
        {
            m_glTexture.create();
            //m_glTexture.setSize(texImage.width(), texImage.height(), texImage.depth());
            m_glTexture.setSize(m_width, m_height);
            m_glTexture.setFormat(m_parameters.gl_textureFormat);
            m_glTexture.allocateStorage();

            QImage tmp(m_width, m_height, m_parameters.imageFormat);
            tmp = tmp.mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip);
            m_glTexture.setData(0, 0, m_parameters.gl_pixelFormat, m_parameters.gl_pixelType, (const void*)tmp.constBits(), 0);
        }
	}

	void GLTexture2D::load(QColor color)
	{
		QImage texImage;
		texImage = QImage(m_width, m_height, m_parameters.imageFormat);
		texImage.fill(color);

		//Need to test
		m_glTexture.create();
		m_glTexture.setSize(texImage.width(), texImage.height(), texImage.depth());
        m_glTexture.setFormat(m_parameters.gl_textureFormat);
		m_glTexture.allocateStorage();

		m_glTexture.setData(texImage.mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip));

		//TO do: Support more QOpenGL features
		m_glTexture.setWrapMode(m_parameters.gl_wrap);
		m_glTexture.setMinMagFilters(m_parameters.gl_filter, m_parameters.gl_filter);
	}

	void GLTexture2D::load(QImage image)
	{
		//Need to test
		m_glTexture.create();
		m_glTexture.setSize(image.width(), image.height(), image.depth());
        m_glTexture.setFormat(m_parameters.gl_textureFormat);
		m_glTexture.allocateStorage();

        QImage tmp = image.convertToFormat(m_parameters.imageFormat);
		tmp = tmp.mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip);
        m_glTexture.setData(0, 0, m_parameters.gl_pixelFormat, m_parameters.gl_pixelType, (const void*)tmp.constBits(), 0);

		//TO do: Support more QOpenGL features
		m_glTexture.setWrapMode(m_parameters.gl_wrap);
		m_glTexture.setMinMagFilters(m_parameters.gl_filter, m_parameters.gl_filter);
	}
}