#include "shaderUniform.h"

namespace CGFF {

	ShaderStruct::ShaderStruct(const QString& name)
		: m_name(name)
		, m_size(0)
		, m_offset(0)
	{
	}

	void ShaderStruct::addField(QSharedPointer<ShaderUniformDeclaration> field)
	{
		m_size += field->getSize();
		int offset = 0;
		if (m_fields.size())
		{
			QSharedPointer<ShaderUniformDeclaration> previous = m_fields.back();
			offset = previous->getOffset() + previous->getSize();
		}
		field->setOffset(offset);
		m_fields.push_back(field);
	}
}