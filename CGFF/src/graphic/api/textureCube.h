#ifndef TEXTURE_CUBE_H
#define TEXTURE_CUBE_H

#include "texture.h"

namespace CGFF {

	class TextureCube : public QOpenGLTexture
	{
	public:
		TextureCube(QOpenGLTexture::Target target = TargetCubeMap);

	protected:
		enum class InputFormat
		{
			VERTICAL_CROSS,
			HORIZONTAL_CROSS
		};
	public:
		static QSharedPointer<TextureCube> createFromFile(const QString& filepath);
		static QSharedPointer<TextureCube> createFromFiles(const QStringList files);
		static QSharedPointer<TextureCube> createFromVCross(const QStringList files, int mips);
	}
}

#endif
