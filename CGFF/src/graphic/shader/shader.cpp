#include "shader.h"
#include "graphic/api/context.h"
#include "platform/opengl/glShader.h"

namespace CGFF {

	const Shader* Shader::s_currentlyBound = nullptr;

	QSharedPointer<Shader> Shader::createFromFile(const QString& name, const QString& vertexFile, const QString& fragmentFile)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
		{
			QSharedPointer<GLShader> tmpShader = QSharedPointer<GLShader>(new GLShader(name));
			tmpShader->createFromFile(vertexFile, fragmentFile);
			return tmpShader;
		}
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
		return nullptr;
	}

	QSharedPointer<Shader> Shader::createFromSource(const QString& name, const QString& vertexSource, const QString& fragmentSource)
	{
		switch (Context::getRenderAPI())
		{
		case RenderAPI::OPENGL:
		{
			QSharedPointer<GLShader> tmpShader = QSharedPointer<GLShader>(new GLShader(name));
			tmpShader->createFromSource(vertexSource, fragmentSource);
			return tmpShader;
		}
		case RenderAPI::DIRECT3D:
			return nullptr;
		}
		return nullptr;
	}
}