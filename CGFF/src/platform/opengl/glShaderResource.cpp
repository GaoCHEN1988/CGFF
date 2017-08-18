#include "glShaderResource.h"

namespace CGFF {


	GLShaderResourceDeclaration::GLShaderResourceDeclaration(Type type, const QString& name, uint count)
		: m_type(type)
		, m_name(name)
		, m_count(count)
		, m_register(0)
	{
	}

	GLShaderResourceDeclaration::Type GLShaderResourceDeclaration::stringToType(const QString& type)
	{
		if (type == "sampler2D")		return GLShaderResourceDeclaration::Type::TEXTURE2D;
		if (type == "samplerCube")		return GLShaderResourceDeclaration::Type::TEXTURECUBE;
		if (type == "samplerShadow")	return GLShaderResourceDeclaration::Type::TEXTURESHADOW;

		return GLShaderResourceDeclaration::Type::NONE;
	}

	QString GLShaderResourceDeclaration::typeToString(GLShaderResourceDeclaration::Type type)
	{
		switch (type)
		{
		case GLShaderResourceDeclaration::Type::TEXTURE2D:		return "sampler2D";
		case GLShaderResourceDeclaration::Type::TEXTURECUBE:	return "samplerCube";
		case GLShaderResourceDeclaration::Type::TEXTURESHADOW:	return "samplerShadow";
		}
		return "Invalid Type";
	}
}