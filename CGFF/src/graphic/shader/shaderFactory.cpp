#include "shaderFactory.h"
#include "graphic/api/context.h"

namespace CGFF {
    QSharedPointer<QOpenGLShaderProgram> DefaultShader()
    {
        QSharedPointer<QOpenGLShaderProgram> shader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);

#ifdef OPENGL_ES
        // load and compile vertex shader
        bool success = shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shaders_es/SimpleVertexShader.vert");
        // load and compile fragment shader
        success = shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shaders_es/SimpleFragmentShader.frag");
#else
        // load and compile vertex shader
        bool success = shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shaders/SimpleVertexShader.vert");
        // load and compile fragment shader
        success = shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shaders/SimpleFragmentShader.frag");
#endif
        shader->link();

        return shader;
    }

    QSharedPointer<QOpenGLShaderProgram> SimpleShader()
    {
        return nullptr;
    }

    QSharedPointer<QOpenGLShaderProgram> BasicLightShader()
    {
        return nullptr;
    }

	QSharedPointer<Shader> BatchRendererShader()
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
			return Shader::createFromFile("BatchRenderer", 
				"src/graphic/shaders/SimpleVertexShader.vert", 
				"src/graphic/shaders/SimpleVertexShader.frag");
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
		return nullptr;
	}
}