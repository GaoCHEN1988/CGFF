#include "glShaderUniform.h"

namespace CGFF {


	GLShaderUniformDeclaration::GLShaderUniformDeclaration(GLShaderUniformDeclaration::Type type, const QString& name, uint count)
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


	uint GLShaderUniformDeclaration::sizeOfUniformType(GLShaderUniformDeclaration::Type type)
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
		case GLShaderUniformDeclaration::Type::QMatrix3x3:			return sizeof(QMatrix3x3);
		case GLShaderUniformDeclaration::Type::QMatrix4x4:			return sizeof(QMatrix4x4);
		}
		return 0;
	}

	GLShaderUniformDeclaration::Type GLShaderUniformDeclaration::stringToType(const QString& type)
	{
		if (type == "int")		return GLShaderUniformDeclaration::Type::GLint;
		if (type == "uint")		return GLShaderUniformDeclaration::Type::GLuint;
		if (type == "float")	return GLShaderUniformDeclaration::Type::GLfloat;
		if (type == "vec2")		return GLShaderUniformDeclaration::Type::QVector2D;
		if (type == "vec3")		return GLShaderUniformDeclaration::Type::QVector3D;
		if (type == "vec4")		return GLShaderUniformDeclaration::Type::QVector4D;
		if (type == "mat2")		return GLShaderUniformDeclaration::Type::QMatrix2x2;
		if (type == "mat3")		return GLShaderUniformDeclaration::Type::QMatrix3x3;
		if (type == "mat4")		return GLShaderUniformDeclaration::Type::QMatrix4x4;

		return Type::NONE;
	}

	QString GLShaderUniformDeclaration::typeToString(GLShaderUniformDeclaration::Type type)
	{
		switch (type)
		{
		case GLShaderUniformDeclaration::Type::GLfloat:				return "float";
		case GLShaderUniformDeclaration::Type::GLint:				return "int";
		case GLShaderUniformDeclaration::Type::GLuint:				return "uint";
		case GLShaderUniformDeclaration::Type::QVector2D:			return "vec2";
		case GLShaderUniformDeclaration::Type::QVector3D:			return "vec3";
		case GLShaderUniformDeclaration::Type::QVector4D:			return "vec4";
		case GLShaderUniformDeclaration::Type::QMatrix2x2:			return "mat2";
		case GLShaderUniformDeclaration::Type::QMatrix3x3:			return "mat3";
		case GLShaderUniformDeclaration::Type::QMatrix4x4:			return "mat4";
		}
		return "Invalid Type";
	}


	GLShaderUniformBufferDeclaration::GLShaderUniformBufferDeclaration(const QString& name, ShaderType shaderType)
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
			QSharedPointer<GLShaderUniformDeclaration> previous = qSharedPointerCast<GLShaderUniformDeclaration>(m_uniforms.back());
			offset = previous->m_offset + previous->m_size;
		}
		uniform->setOffset(offset);
		m_size += uniform->getSize();
		m_uniforms.push_back(uniform);
	}

	QSharedPointer<ShaderUniformDeclaration> GLShaderUniformBufferDeclaration::findUniform(const QString& name)
	{
		for (QSharedPointer<ShaderUniformDeclaration> uniform : m_uniforms)
		{
			if (uniform->getName() == name)
				return uniform;
		}
		return nullptr;
	}

}