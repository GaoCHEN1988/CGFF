#include "glTextureCube.h"

namespace CGFF {

	GLTextureCube::GLTextureCube(const QString& name, const QString& filepath)
		: m_name(name)
		, m_inputFormat(InputFormat::VERTICAL_CROSS)
	{
		m_fileNames.append(filepath);
		loadFromFiles();
	}

	GLTextureCube::GLTextureCube(const QString& name, const QStringList& files)
		: m_name(name)
		, m_fileNames(files)
		, m_inputFormat(InputFormat::VERTICAL_CROSS)
	{
		loadFromFiles();
	}

	GLTextureCube::GLTextureCube(const QString& name, const QStringList& files, int mips, InputFormat format)
		: m_name(name)
		, m_fileNames(files)
		, m_inputFormat(format)
	{
		loadFromFiles();
	}

	void GLTextureCube::loadFromFiles()
	{
		if (m_fileNames.size == 1)
		{
			//To do
		}
        else if (m_fileNames.size == 6)
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
			QOpenGLTexture::create();
			QOpenGLTexture::setFormat(m_parameters.textureFormat);
			QOpenGLTexture::allocateStorage();
			
			QOpenGLTexture::setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
				m_parameters.pixelFormat, m_parameters.pixelType,
				(const void*)posx.constBits(), 0);
			QOpenGLTexture::setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
				m_parameters.pixelFormat, m_parameters.pixelType,
				(const void*)posy.constBits(), 0);
			QOpenGLTexture::setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
				m_parameters.pixelFormat, m_parameters.pixelType,
				(const void*)posz.constBits(), 0);
			QOpenGLTexture::setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
				m_parameters.pixelFormat, m_parameters.pixelType,
				(const void*)negx.constBits(), 0);
			QOpenGLTexture::setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
				m_parameters.pixelFormat, m_parameters.pixelType,
				(const void*)negy.constBits(), 0);
			QOpenGLTexture::setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
				m_parameters.pixelFormat, m_parameters.pixelType,
				(const void*)negz.constBits(), 0);

			QOpenGLTexture::generateMipMaps();
			QOpenGLTexture::setWrapMode(m_parameters.wrap);
			QOpenGLTexture::setMinMagFilters(m_parameters.filter, m_parameters.filter);

		}
		else
		{
			qFatal("Image count for texture cube is not correct.");
		}

	}
}