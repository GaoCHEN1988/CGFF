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
		GLShader(const QString& name);
		virtual ~GLShader();

		void createFromFile(const QString& vertexFile, const QString& fragmentFile, const QString& geometryFile = "");
		void createFromSource(const QString& vertexSource, const QString& fragmentSource, const QString& geometrySource = "");

		void init();
		void close() override;
		void bind() override;
		void unBind() override;
		void reload() override;

		void setVSSystemUniformBuffer(uchar* data, uint size, uint slot = 0) override;
		void setPSSystemUniformBuffer(uchar* data, uint size, uint slot = 0) override;

		void setVSUserUniformBuffer(uchar* data, uint size) override;
		void setPSUserUniformBuffer(uchar* data, uint size) override;

		void setUniform(const QString& name, uchar* data);
		void resolveAndSetUniformField(const QSharedPointer<GLShaderUniformDeclaration>& field, uchar* data, int offset);

        QVector<UniformInfo> getShaderUniformsInfo() const override;
        QVector<ShaderResourceUniformInfo> getShaderResourcesInfo() const override;

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

		void load();
		QSharedPointer<ShaderUniformDeclaration> findUniformDeclaration(const QString& name, QSharedPointer<ShaderUniformBufferDeclaration> buffer);
		QSharedPointer<ShaderUniformDeclaration> findUniformDeclaration(const QString& name);
		void resolveAndSetUniforms(const QSharedPointer<ShaderUniformBufferDeclaration>& buffer, uchar* data);
		void resolveAndSetUniform(const QSharedPointer<GLShaderUniformDeclaration>& uniform, uchar* data);
        void setUniformStruct(const QSharedPointer<GLShaderUniformDeclaration>& uniform, uchar* data, int offset);
        void setUniformStructList(const QSharedPointer<GLShaderUniformDeclaration>& uniform, uchar* data, int offset);

		void parse(const QString& vertexSource, const QString& fragmentSource, const QString& geometrySource = "");
		void parseUniform(const QString& statement, ShaderType shaderType);
		void parseUniformStruct(const QString& block, ShaderType shaderType);

		bool isTypeStringResource(const QString& type);
		QSharedPointer<ShaderStruct> findStruct(const QString& name);

        void resolveUniformLists(const ShaderUniformList& uniformBufferList);
        void resolveUniformBufferLists(const ShaderUniformBufferList& uniformBufferList);
        void resolveUniforms();

	private:
		QOpenGLShaderProgram m_glShaderProgram;
		QString m_name;
		QString m_vertexFile;
		QString m_vertexSource;
		QString m_fragmentFile;
		QString m_fragmentSource;
        QString m_geometryFile;
        QString m_geometrySource;

		ShaderUniformBufferList m_VSUniformBuffers;
		ShaderUniformBufferList m_PSUniformBuffers;
		QSharedPointer<GLShaderUniformBufferDeclaration> m_VSUserUniformBuffer;
		QSharedPointer<GLShaderUniformBufferDeclaration> m_PSUserUniformBuffer;
		ShaderResourceList m_resources;
		ShaderStructList m_structs;

	};
}

#endif