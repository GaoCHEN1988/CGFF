#include "texture2D.h"
#include "context.h"
#include "platform/opengl/glTexture2D.h"

namespace CGFF {

	QSharedPointer<Texture2D> Texture2D::Create(int width, int height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions())
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return QSharedPointer<Texture2D>(new GLTexture2D(width, height, parameters, loadOptions));
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
	}

	QSharedPointer<Texture2D> Texture2D::CreateFromFile(const QString& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions())
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return QSharedPointer<Texture2D>(new GLTexture2D(filepath, filepath, parameters, loadOptions));
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
	}

    QSharedPointer<Texture2D> Texture2D::createFromFile(const QString& name, const QString& filepath, TextureParameters parameters, TextureLoadOptions loadOptions)
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:		
            return QSharedPointer<Texture2D>(new GLTexture2D(name, filepath, parameters, loadOptions));
        case RenderAPI::DIRECT3D:	
            return nullptr;
        }
    }

}