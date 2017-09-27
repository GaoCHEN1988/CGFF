#ifndef CGFF_GL_SHADER_RESOURCE_H
#define CGFF_GL_SHADER_RESOURCE_H

#include "graphic/shader/shaderResource.h"

namespace CGFF {

	class GLShaderResourceDeclaration : public ShaderResourceDeclaration
	{
	public:
		GLShaderResourceDeclaration(Type type, const QString& name, uint count);

		inline QString getName() const override { return m_name; }
		inline uint getRegister() const override { return m_register; }
		inline uint getCount() const override { return m_count; }

		inline Type getType() const override { return m_type; }
	public:
		static GLShaderResourceDeclaration::Type stringToType(const QString& type);
		static QString typeToString(GLShaderResourceDeclaration::Type type);

	private:
		friend class GLShader;
	private:
		QString m_name;
		uint m_register;
		uint m_count;
		Type m_type;
	};

}

#endif
