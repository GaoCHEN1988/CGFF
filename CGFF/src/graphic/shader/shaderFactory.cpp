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
            switch (Context::getRenderAPI())
            {
            case RenderAPI::OPENGL:
                return Shader::createFromFile("SimpleShader",
                    "/shaders/SimpleVertexShader.vert",
                    "/shaders/SimpleFragmentShader.frag");
            case RenderAPI::DIRECT3D:
                return nullptr;
            }
            return nullptr;
        }

        QSharedPointer<Shader> FramebufferShader()
        {
            switch (Context::getRenderAPI())
            {
            case RenderAPI::OPENGL:
                return Shader::createFromFile("FramebufferShader",
                    "/shaders/fbVertexShader.vert",
                    "/shaders/fbfragmentShader.frag");
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
    }
}