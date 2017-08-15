#include "glShaderResource.h"

namespace CGFF {


	GLShaderResourceDeclaration::GLShaderResourceDeclaration(Type type, const QString& name, uint count)
		: m_type(type)
		, m_name(name)
		, m_count(count)
		, m_register(0)
	{
	}
}