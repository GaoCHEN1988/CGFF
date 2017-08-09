#include "textureCube.h"
#include "context.h"
#include "platform/opengl/glTextureCube.h"

namespace CGFF {

	QSharedPointer<TextureCube> TextureCube::createFromFile(const QString& filepath)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return QSharedPointer<TextureCube>(new GLTextureCube(filepath, filepath));
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
	}

	QSharedPointer<TextureCube> TextureCube::createFromFiles(const QStringList files)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return QSharedPointer<TextureCube>(new GLTextureCube(files[0], files));
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
	}

	QSharedPointer<TextureCube> TextureCube::createFromVCross(const QStringList files, int mips)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return QSharedPointer<TextureCube>(nullptr); //To do: implement
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
	}
}
