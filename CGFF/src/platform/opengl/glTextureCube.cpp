#include "glTextureCube.h"

namespace CGFF {

	GLTextureCube::GLTextureCube(const QString& name, const QString& filepath)
		: m_name(name)
		, m_inputFormat(InputFormat::VERTICAL_CROSS)
		, m_glTexture(m_glTexture.TargetCubeMap)
	{
		m_fileNames.append(filepath);
		loadFromFiles();
	}

	GLTextureCube::GLTextureCube(const QString& name, const QStringList& files)
		: m_name(name)
		, m_fileNames(files)
		, m_inputFormat(InputFormat::VERTICAL_CROSS)
		, m_glTexture(m_glTexture.TargetCubeMap)
	{
		loadFromFiles();
	}

	GLTextureCube::GLTextureCube(const QString& name, const QStringList& files, int mips, InputFormat format)
		: m_name(name)
		, m_fileNames(files)
		, m_inputFormat(format)
		, m_glTexture(m_glTexture.TargetCubeMap)
	{
		loadFromFiles();
	}

	void GLTextureCube::bind(uint slot)
	{
		m_glTexture.bind(slot);
	}

	void GLTextureCube::unBind(uint slot)
	{
		m_glTexture.release(slot);
	}

	void GLTextureCube::loadFromFiles()
	{
		if (m_fileNames.size() == 1)
		{
			//To do
		}
        else if (m_fileNames.size() == 6)
		{

			QImage posx = QImage(m_fileNames[0]).mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);
			QImage negx = QImage(m_fileNames[1]).mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);

			QImage posy = QImage(m_fileNames[2]).mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);
			QImage negy = QImage(m_fileNames[3]).mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);

			QImage posz = QImage(m_fileNames[4]).mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);
			QImage negz = QImage(m_fileNames[5]).mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);

			if (posx.isNull() || negx.isNull() || posy.isNull() || negy.isNull() || posz.isNull() || negz.isNull())
			{
				qFatal("Load images for texture cube is not correct.");
				return;
			}

			//Need to test
			m_glTexture.create();
			m_glTexture.setSize(posx.width(), posx.height(), posx.depth());
			m_glTexture.setFormat(m_parameters.gl_textureFormat);
			m_glTexture.allocateStorage();
			
			m_glTexture.setData(0, 0, m_glTexture.CubeMapPositiveX,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)posx.constBits(), 0);
			m_glTexture.setData(0, 0, m_glTexture.CubeMapPositiveY,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)posy.constBits(), 0);
			m_glTexture.setData(0, 0, m_glTexture.CubeMapPositiveZ,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)posz.constBits(), 0);
			m_glTexture.setData(0, 0, m_glTexture.CubeMapNegativeX,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)negx.constBits(), 0);
			m_glTexture.setData(0, 0, m_glTexture.CubeMapNegativeY,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)negy.constBits(), 0);
			m_glTexture.setData(0, 0, m_glTexture.CubeMapNegativeZ,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)negz.constBits(), 0);

			m_glTexture.generateMipMaps();
			m_glTexture.setWrapMode(m_parameters.gl_wrap);
			m_glTexture.setMinMagFilters(m_parameters.gl_filter, m_parameters.gl_filter);

		}
		else
		{
			qFatal("Image count for texture cube is not correct.");
		}

	}
}