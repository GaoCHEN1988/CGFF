#include "glShaderUniform.h"

namespace CGFF {


	GLShaderUniformDeclaration::GLShaderUniformDeclaration(Type type, const QString& name, uint count)
		: m_type(type)
		, m_name(name)
		, m_count(count)
	{
		m_size = sizeOfUniformType(m_type) * m_count;
	}

	GLShaderUniformDeclaration::GLShaderUniformDeclaration(QSharedPointer<ShaderStruct> uniformStruct, const QString& name, uint count)
		: m_struct(uniformStruct)
		, m_name(name)
		, m_count(count)
		, m_type(GLShaderUniformDeclaration::Type::STRUCT)
	{
		m_size = m_struct->getSize() * count;
	}

	void GLShaderUniformDeclaration::setOffset(uint offset)
	{
		if (m_type == GLShaderUniformDeclaration::Type::STRUCT)
			m_struct->setOffset(offset);

		m_offset = offset;
	}


	uint GLShaderUniformDeclaration::sizeOfUniformType(Type type)
	{
		switch (type)
		{
		case GLShaderUniformDeclaration::Type::GLfloat:				return sizeof(GLfloat);
		case GLShaderUniformDeclaration::Type::GLint:				return sizeof(GLint);
		case GLShaderUniformDeclaration::Type::GLuint:				return sizeof(GLuint);
		case GLShaderUniformDeclaration::Type::QVector2D:			return sizeof(QVector2D);
		case GLShaderUniformDeclaration::Type::QVector3D:			return sizeof(QVector3D);
		case GLShaderUniformDeclaration::Type::QVector4D:			return sizeof(QVector4D);
		case GLShaderUniformDeclaration::Type::QMatrix2x2:			return sizeof(QMatrix2x2);
		case GLShaderUniformDeclaration::Type::QMatrix2x3:			return sizeof(QMatrix2x3);
		case GLShaderUniformDeclaration::Type::QMatrix2x4:			return sizeof(QMatrix2x4);
		case GLShaderUniformDeclaration::Type::QMatrix3x2:			return sizeof(QMatrix3x2);
		case GLShaderUniformDeclaration::Type::QMatrix3x3:			return sizeof(QMatrix3x3);
		case GLShaderUniformDeclaration::Type::QMatrix3x4:			return sizeof(QMatrix3x4);
		case GLShaderUniformDeclaration::Type::QMatrix4x2:			return sizeof(QMatrix4x2);
		case GLShaderUniformDeclaration::Type::QMatrix4x3:			return sizeof(QMatrix4x3);
		case GLShaderUniformDeclaration::Type::QMatrix4x4:			return sizeof(QMatrix4x4);
		}
		return 0;
	}


	GLShaderUniformBufferDeclaration::GLShaderUniformBufferDeclaration(const QString& name, uint shaderType)
		: m_name(name)
		, m_shaderType(shaderType)
		, m_size(0)
		, m_register(0)
	{

	}

	void GLShaderUniformBufferDeclaration::pushUniform(QSharedPointer<GLShaderUniformDeclaration> uniform)
	{
		uint offset = 0;
		if (m_uniforms.size())
		{
			QSharedPointer<GLShaderUniformDeclaration> previous = m_uniforms.back();
			offset = previous->m_offset + previous->m_size;
		}
		uniform->setOffset(offset);
		m_size += uniform->getSize();
		m_uniforms.push_back(uniform);
	}

	QSharedPointer<ShaderUniformDeclaration> GLShaderUniformBufferDeclaration::findUniform(const QString& name)
	{
		for (QSharedPointer<GLShaderUniformDeclaration> uniform : m_uniforms)
		{
			if (uniform->getName() == name)
				return uniform;
		}
		return nullptr;
	}

}