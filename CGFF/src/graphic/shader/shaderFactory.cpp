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

        QSharedPointer<Shader> FramebufferShader()
        {
            switch (Context::getRenderAPI())
            {
            case RenderAPI::OPENGL:
                return Shader::createFromFile("FramebufferShader",
                    "/shaders/framebuffer.vert",
                    "/shaders/framebuffer.frag");
            case RenderAPI::DIRECT3D:
                return nullptr;
            }
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

		QSharedPointer<Shader> DebugSceneShader()
		{
			switch (Context::getRenderAPI())
			{
			case RenderAPI::OPENGL:
				return Shader::createFromFile("DebugSceneShader",
					"/shaders/debugScene.vert",
					"/shaders/debugScene.frag");
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
                    "/shaders/debug.vert",
                    "/shaders/debug.frag");
            case RenderAPI::DIRECT3D:
                return nullptr;
            }
            return nullptr;
        }
	}
}