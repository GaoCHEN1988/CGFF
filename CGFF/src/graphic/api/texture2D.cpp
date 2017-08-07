#include "texture2D.h"
#include "context.h"

namespace CGFF {

	Texture2D::Texture2D(QOpenGLTexture::Target target)
	: QOpenGLTexture(target)
	{
	}

    QSharedPointer<Texture2D> Texture2D::createFromFile(const QString& name, const QString& filepath)
    {
        switch (Context::getRenderAPI())
        {
        case RenderAPI::OPENGL:		
            return nullptr;
        case RenderAPI::DIRECT3D:	
            return nullptr;
        }
    }

}