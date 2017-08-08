#include "glTexture2D.h"

namespace CGFF {

	GLTexture2D::GLTexture2D(int width, int height, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_name("")
		, m_fileName("")
		, m_width(width)
		, m_height(height)
		, m_parameters(parameters)
		, m_loadOptions(loadOptions)
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
	{
		load(color);
	}

	GLTexture2D::GLTexture2D(const QString& name, const QString& filename, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_name(name)
		, m_fileName(filename)
		, m_width(1)
		, m_height(1)
		, m_parameters(parameters)
		, m_loadOptions(loadOptions)
	{
		load();
	}

	void GLTexture2D::load(QColor color)
	{
		//Need to test
		QOpenGLTexture::create();
		QOpenGLTexture::allocateStorage();

		QImage texImage;

		if (!m_fileName.isEmpty())
		{
			if (texImage.load(m_fileName))
			{
				setFormat(m_parameters.textureFormat);
				setData(texImage.mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat));
			}
			else
			{
				qWarning("Can't load image from ", m_fileName);
				return;
			}
		}
		else
		{
			texImage = QImage(m_width, m_height, m_parameters.imageFormat);
			texImage.fill(color);
			setFormat(m_parameters.textureFormat);
			setData(texImage.mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip));
		}
		
		//TO do: Support more QOpenGL features
		setWrapMode(m_parameters.wrap);
		setMinMagFilters(m_parameters.filter, m_parameters.filter);
	}

}