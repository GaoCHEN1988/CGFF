#ifndef CGFF_GL_SHADER_UNIFORM_H
#define CGFF_GL_SHADER_UNIFORM_H

#include "graphic/shader/shaderUniform.h"

namespace CGFF {

	class GLShaderUniformDeclaration : public ShaderUniformDeclaration
	{
	public:
		enum class Type
		{
			NONE,
            GLboolean,
			GLfloat,
			GLint,
			GLuint,
			QVector2D,
			QVector3D,
			QVector4D,
			QMatrix2x2,
			QMatrix3x3,
			QMatrix4x4,
			STRUCT
		};

	public:
		GLShaderUniformDeclaration(GLShaderUniformDeclaration::Type type, const QString& name, uint count = 1);
		GLShaderUniformDeclaration(QSharedPointer<ShaderStruct> uniformStruct, const QString& name, uint count = 1);

		inline QString getName() const override { return m_name; }
		inline uint getSize() const override { return m_size; }
		inline uint getCount() const override { return m_count; }
		inline uint getOffset() const override { return m_offset; }
		inline uint getAbsoluteOffset() const { return m_struct ? m_struct->getOffset() + m_offset : m_offset; }

		int getLocation() const { return m_location; }
		inline GLShaderUniformDeclaration::Type getType() const { return m_type; }
		inline const ShaderStruct& getShaderUniformStruct() const { Q_ASSERT(m_struct); return *m_struct; }

	protected:
		void setOffset(uint offset) override;

	public:
		static uint sizeOfUniformType(GLShaderUniformDeclaration::Type type);
		static GLShaderUniformDeclaration::Type stringToType(const QString& type);
		static QString typeToString(GLShaderUniformDeclaration::Type type);

	private:
		friend class GLShader;
		friend class GLShaderUniformBufferDeclaration;

	private:
		QString m_name;
		uint m_size;
		uint m_count;
		uint m_offset;
		GLShaderUniformDeclaration::Type m_type;
		QSharedPointer<ShaderStruct> m_struct;
		mutable int m_location;
	};

	struct GLShaderUniformField
	{
		GLShaderUniformDeclaration::Type type;
		QString name;
		uint count;
		mutable uint size;
		mutable int location;
	};

	// TODO: Eventually support OpenGL uniform buffers. This is more platform-side.
	class GLShaderUniformBufferDeclaration : public ShaderUniformBufferDeclaration
	{
	public:
		GLShaderUniformBufferDeclaration(const QString& name, ShaderType shaderType);

		void pushUniform(QSharedPointer<GLShaderUniformDeclaration> uniform);

		inline QString getName() const override { return m_name; }
		inline uint getRegister() const override { return m_register; }
		inline ShaderType getShaderType() const override { return m_shaderType; }
		inline uint getSize() const override { return m_size; }
		inline const ShaderUniformList& getUniformDeclarations() const override { return m_uniforms; }

		QSharedPointer<ShaderUniformDeclaration> findUniform(const QString& name) override;

	private:
		friend class Shader;
	private:
		QString m_name;
		ShaderUniformList m_uniforms;
		uint m_register;
		uint m_size;
		ShaderType m_shaderType; // 0 = VS, 1 = PS
	};
}

#endif