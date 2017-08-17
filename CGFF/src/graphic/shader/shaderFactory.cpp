#include "shaderFactory.h"
#include "graphic/api/context.h"

namespace CGFF {
    QSharedPointer<Shader> DefaultShader()
    {
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return Shader::createFromFile("DefaultShader",
				"src/graphic/shaders/SimpleVertexShader.vert",
				"src/graphic/shaders/SimpleFragmentShader.frag");
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
		return nullptr;
    }

    QSharedPointer<Shader> SimpleShader()
    {
        return nullptr;
    }

    QSharedPointer<Shader> BasicLightShader()
    {
        return nullptr;
    }

	QSharedPointer<Shader> BatchRendererShader()
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return Shader::createFromFile("BatchRenderer", 
				"src/graphic/shaders/BatchRenderer.vert", 
				"src/graphic/shaders/BatchRenderer.frag");
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
		return nullptr;
	}
}