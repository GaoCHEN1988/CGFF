#include "shaderFactory.h"
#include "graphic/api/context.h"

namespace CGFF {
	namespace ShaderFactory {

		QSharedPointer<Shader> DefaultShader()
		{
			switch (Context::getRenderAPI())
			{
			case RenderAPI::OPENGL:
				return Shader::createFromFile("DefaultShader",
					"/shaders/SimpleVertexShader.vert",
					"/shaders/SimpleFragmentShader.frag");
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
					"/shaders/BatchRenderer.vert",
					"/shaders/BatchRenderer.frag");
			case RenderAPI::DIRECT3D:
				return nullptr;
			}
			return nullptr;
		}

		QSharedPointer<Shader> DebugShader()
		{
			switch (Context::getRenderAPI())
			{
			case RenderAPI::OPENGL:
				return Shader::createFromFile("DebugShader",
					"/shaders/debugScene.vert",
					"/shaders/debugScene.frag");
			case RenderAPI::DIRECT3D:
				return nullptr;
			}
			return nullptr;
		}
	}
}