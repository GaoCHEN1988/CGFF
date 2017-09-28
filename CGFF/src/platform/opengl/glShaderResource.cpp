#include "glShaderResource.h"

namespace CGFF {


	GLShaderResourceDeclaration::GLShaderResourceDeclaration(ShaderResourceType type, const QString& name, uint count)
		: m_type(type)
		, m_name(name)
		, m_count(count)
		, m_register(0)
	{
	}

	ShaderResourceType GLShaderResourceDeclaration::stringToType(const QString& type)
	{
		if (type == "sampler2D")		return ShaderResourceType::TEXTURE2D;
		if (type == "samplerCube")		return ShaderResourceType::TEXTURECUBE;
		if (type == "samplerShadow")	return ShaderResourceType::TEXTURESHADOW;

		return ShaderResourceType::NONE;
	}

	QString GLShaderResourceDeclaration::typeToString(ShaderResourceType type)
	{
		switch (type)
		{
		case ShaderResourceType::TEXTURE2D:		return "sampler2D";
		case ShaderResourceType::TEXTURECUBE:	return "samplerCube";
		case ShaderResourceType::TEXTURESHADOW:	return "samplerShadow";
		}
		return "Invalid Type";
	}
}