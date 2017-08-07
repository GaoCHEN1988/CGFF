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
		load();
	}

	GLTexture2D::GLTexture2D(const QString& name, const QString& filename, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_name(name)
		, m_fileName(filename)
		, m_width(0)
		, m_height(0)
		, m_parameters(parameters)
		, m_loadOptions(loadOptions)
	{
		load();
	}

	void GLTexture2D::load()
	{
		QImage texImage;

		if (!m_fileName.isEmpty())
		{
			texImage.load(m_fileName);
			setData(texImage);
		}
	}

}