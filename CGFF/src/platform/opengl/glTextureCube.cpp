#include "glTextureCube.h"

namespace CGFF {

	GLTextureCube::GLTextureCube(const QString& name, const QString& filepath)
		: m_name(name)
		, m_inputFormat(InputFormat::VERTICAL_CROSS)
		, m_glTexture(QOpenGLTexture::TargetCubeMap)
		, m_width(0)
		, m_height(0)
	{
		m_fileNames.append(filepath);
		loadFromFiles();
	}

	GLTextureCube::GLTextureCube(const QString& name, const QStringList& files)
		: m_name(name)
		, m_fileNames(files)
		, m_inputFormat(InputFormat::VERTICAL_CROSS)
		, m_glTexture(QOpenGLTexture::TargetCubeMap)
		, m_width(0)
		, m_height(0)
	{
		loadFromFiles();
	}

	GLTextureCube::GLTextureCube(const QString& name, const QStringList& files, int mips, InputFormat format)
		: m_name(name)
		, m_fileNames(files)
		, m_inputFormat(format)
		, m_glTexture(QOpenGLTexture::TargetCubeMap)
		, m_width(0)
		, m_height(0)
	{
		if (m_inputFormat == InputFormat::VERTICAL_CROSS)
			loadFromVCross(mips);
		else
			qFatal("Horizontal cross not implemented!");
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
		if (m_fileNames.size() == 6)
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
			m_glTexture.bind();
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
			m_glTexture.release();
		}
		else
		{
			qFatal("Image count for texture cube is not correct.");
		}

	}

	void GLTextureCube::loadFromVCross(int mips)
	{
		uint srcWidth, srcHeight;

		QImage** cubeTextureData = new QImage*[mips];
		for (uint i = 0; i < mips; i++)
			cubeTextureData[i] = new QImage[6];

		QVector<uint> faceWidths;
		faceWidths.resize(mips);
		QVector<uint> faceHeights;
		faceHeights.resize(mips);

		for (int i = 0; i < mips; i++)
		{
			QImage image = QImage(m_fileNames[i]);

			if (image.isNull())
			{
				qFatal("Load images for texture cube is not correct.");
				return;
			}

			uint face = 0;
			uint faceWidth = image.width() / 3;
			uint faceHeight = image.height() / 4;

			faceWidths[i] = faceWidth;
			faceHeights[i] = faceHeight;

			for (uint cy = 0; cy < 4; cy++)
			{
				for (uint cx = 0; cx < 3; cx++)
				{
					if (cy == 0 || cy == 2 || cy == 3)
					{
						if (cx != 1)
							continue;
					}
					
					int px = faceWidth * cy;

					int py = faceHeight * cy;

					cubeTextureData[i][face] = image.copy(QRect(px, py, faceWidth, faceHeight));

					face++;
				}
			}

		}

		//Test
		m_glTexture.create();
		m_glTexture.setSize(cubeTextureData[0][0].width(), cubeTextureData[0][0].height(), cubeTextureData[0][0].depth());
		m_glTexture.setFormat(m_parameters.gl_textureFormat);
		m_glTexture.allocateStorage();

		for (uint m = 0; m < mips; m++)
		{
			QImage posx = cubeTextureData[m][3].mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);
			QImage negx	= cubeTextureData[m][1].mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);
			QImage posy	= cubeTextureData[m][0].mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);
			QImage negy	= cubeTextureData[m][4].mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);
			QImage posz	= cubeTextureData[m][2].mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);
			QImage negz	= cubeTextureData[m][5].mirrored(m_loadOptions.horizontalFlip, m_loadOptions.verticalFlip).convertToFormat(m_parameters.imageFormat);

			m_glTexture.setData(m, 0, m_glTexture.CubeMapPositiveX,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)posx.constBits(), 0);
			m_glTexture.setData(m, 0, m_glTexture.CubeMapPositiveY,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)posy.constBits(), 0);
			m_glTexture.setData(m, 0, m_glTexture.CubeMapPositiveZ,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)posz.constBits(), 0);
			m_glTexture.setData(m, 0, m_glTexture.CubeMapNegativeX,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)negx.constBits(), 0);
			m_glTexture.setData(m, 0, m_glTexture.CubeMapNegativeY,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)negy.constBits(), 0);
			m_glTexture.setData(m, 0, m_glTexture.CubeMapNegativeZ,
				m_parameters.gl_pixelFormat, m_parameters.gl_pixelType,
				(const void*)negz.constBits(), 0);
		}

		m_glTexture.setWrapMode(m_parameters.gl_wrap);
		m_glTexture.setMinMagFilters(m_parameters.gl_filter, m_parameters.gl_filter);
		m_glTexture.release();

		for (uint i = 0; i < mips; i++)
		{
			delete[] cubeTextureData[i];
		}
		delete[] cubeTextureData;
	}
}