#ifndef CGFF_GL_SHADER_H
#define CGFF_GL_SHADER_H

#include "graphic/shader/shader.h"
#include "glShaderUniform.h"
#include "glShaderResource.h"

#include <QOpenGLShaderProgram>

namespace CGFF {

	class GLShader : public Shader
	{
	public:
		GLShader(QString name);
		virtual ~GLShader();

		void createFromFile(QString vertexFile, QString fragmentFile);
		void createFromSource(QString vertexSource, QString fragmentSource);

		void init();
		void close() override;
		void bind() override;
		void unBind() override;


		void setVSSystemUniformBuffer(uchar* data, uint size, uint slot = 0) override;
		void setPSSystemUniformBuffer(uchar* data, uint size, uint slot = 0) override;

		void setVSUserUniformBuffer(uchar* data, uint size) override;
		void setPSUserUniformBuffer(uchar* data, uint size) override;

		void setUniform(const QString& name, uchar* data);
		void resolveAndSetUniformField(const QSharedPointer<GLShaderUniformDeclaration>& field, uchar* data, int offset);

		inline QString getName() const override { return m_name; };
		inline const ShaderUniformBufferList& getVSSystemUniforms() const override
		{
			return m_VSUniformBuffers;
		}
		inline const ShaderUniformBufferList& getPSSystemUniforms() const override
		{
			return m_PSUniformBuffers;
		}
		inline const QSharedPointer<ShaderUniformBufferDeclaration> getVSUserUniformBuffer() const override 
		{ 
			return m_VSUserUniformBuffer;
		}
		inline const QSharedPointer<ShaderUniformBufferDeclaration> getPSUserUniformBuffer() const override
		{
			return m_PSUserUniformBuffer;
		}
		inline const ShaderResourceList& getResources() const override
		{
			return m_resources;
		}

	private:
		friend class Shader;
		friend class ShaderManager;

		void load(bool isFromFile);
		QSharedPointer<ShaderUniformBufferDeclaration> findUniformDeclaration(const QString& name, QSharedPointer<ShaderUniformBufferDeclaration> buffer);
		QSharedPointer<ShaderUniformBufferDeclaration> findUniformDeclaration(const QString& name);
		void resolveAndSetUniforms(QSharedPointer<ShaderUniformBufferDeclaration> buffer, uchar* data);
		void resolveAndSetUniform(QSharedPointer<GLShaderUniformDeclaration> uniform, uchar* data);
		void setUniformStruct(QSharedPointer<GLShaderUniformDeclaration> uniform, uchar* data, int offset);

		QSharedPointer<ShaderStruct> findStruct(const QString& name);

		void resolveUniforms();

	private:
		QOpenGLShaderProgram m_glShaderProgram;
		QString m_name;
		QString m_vertexFile;
		QString m_vertexSource;
		QString m_fragmentFile;
		QString m_fragmentSource;

		ShaderUniformBufferList m_VSUniformBuffers;
		ShaderUniformBufferList m_PSUniformBuffers;
		QSharedPointer<GLShaderUniformBufferDeclaration> m_VSUserUniformBuffer;
		QSharedPointer<GLShaderUniformBufferDeclaration> m_PSUserUniformBuffer;
		ShaderResourceList m_resources;
		ShaderStructList m_structs;

	};
}

#endif