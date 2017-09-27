#include "glShaderUniform.h"

namespace CGFF {


	GLShaderUniformDeclaration::GLShaderUniformDeclaration(UniformType type, const QString& name, uint count)
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
		, m_type(UniformType::STRUCT)
	{
		m_size = m_struct->getSize() * count;
	}

	void GLShaderUniformDeclaration::setOffset(uint offset)
	{
		if (m_type == UniformType::STRUCT)
			m_struct->setOffset(offset);

		m_offset = offset;
	}


	uint GLShaderUniformDeclaration::sizeOfUniformType(UniformType type)
	{
		switch (type)
		{
		case UniformType::GLfloat:				return sizeof(GLfloat);
		case UniformType::GLint:				return sizeof(GLint);
		case UniformType::GLuint:				return sizeof(GLuint);
		case UniformType::QVector2D:			return sizeof(QVector2D);
		case UniformType::QVector3D:			return sizeof(QVector3D);
		case UniformType::QVector4D:			return sizeof(QVector4D);
		case UniformType::QMatrix2x2:			return sizeof(QMatrix2x2);
		case UniformType::QMatrix3x3:			return sizeof(QMatrix3x3);
		case UniformType::QMatrix4x4:			return sizeof(QMatrix4x4);
		}
		return 0;
	}

	UniformType GLShaderUniformDeclaration::stringToType(const QString& type)
	{
		if (type == "int")		return UniformType::GLint;
		if (type == "uint")		return UniformType::GLuint;
		if (type == "float")	return UniformType::GLfloat;
		if (type == "vec2")		return UniformType::QVector2D;
		if (type == "vec3")		return UniformType::QVector3D;
		if (type == "vec4")		return UniformType::QVector4D;
		if (type == "mat2")		return UniformType::QMatrix2x2;
		if (type == "mat3")		return UniformType::QMatrix3x3;
		if (type == "mat4")		return UniformType::QMatrix4x4;

		return UniformType::NONE;
	}

	QString GLShaderUniformDeclaration::typeToString(UniformType type)
	{
		switch (type)
		{
		case UniformType::GLfloat:				return "float";
		case UniformType::GLint:				return "int";
		case UniformType::GLuint:				return "uint";
		case UniformType::QVector2D:			return "vec2";
		case UniformType::QVector3D:			return "vec3";
		case UniformType::QVector4D:			return "vec4";
		case UniformType::QMatrix2x2:			return "mat2";
		case UniformType::QMatrix3x3:			return "mat3";
		case UniformType::QMatrix4x4:			return "mat4";
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