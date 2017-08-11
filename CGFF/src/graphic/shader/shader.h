#ifndef CGFF_SHADER_H
#define CGFF_SHADER_H

#include "utils/qtopengl.h"
#include "shaderUniform.h"
#include "shaderResource.h"

namespace CGFF {

	class Shader
	{
	public:
		virtual void bind() = 0;
		virtual void unBind() = 0;
		virtual void close() = 0;

		//virtual void setVSSystemUniformBuffer(byte* data, uint size, uint slot = 0) = 0;
		//virtual void setPSSystemUniformBuffer(byte* data, uint size, uint slot = 0) = 0;

		//virtual void setVSUserUniformBuffer(byte* data, uint size) = 0;
		//virtual void setPSUserUniformBuffer(byte* data, uint size) = 0;

		//virtual const ShaderUniformBufferList& getVSSystemUniforms() const = 0;
		//virtual const ShaderUniformBufferList& getPSSystemUniforms() const = 0;
		//virtual const ShaderUniformBufferDeclaration* getVSUserUniformBuffer() const = 0;
		//virtual const ShaderUniformBufferDeclaration* getPSUserUniformBuffer() const = 0;

		//virtual const ShaderResourceList& getResources() const = 0;

		virtual QString getName() const = 0;
		//virtual QString getFilePath() const = 0;

		// virtual void SetData(byte* data, uint size) = 0;

		// bool HasUniform(const String& name) const = 0;
	public:
		static QSharedPointer<Shader> createFromFile(const QString& name, const QString& vertexFile, const QString& fragmentFile);
		static QSharedPointer<Shader> createFromSource(const QString& name, const QString& vertexSource, const QString& fragmentSource);

	public:
		static const Shader* s_currentlyBound;
	};
}

#endif