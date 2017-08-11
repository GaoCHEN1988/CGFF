#ifndef CGFF_TEXTURE_CUBE_H
#define CGFF_TEXTURE_CUBE_H

#include "texture.h"

namespace CGFF {

	class TextureCube : public Texture
	{
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
	};
}

#endif
