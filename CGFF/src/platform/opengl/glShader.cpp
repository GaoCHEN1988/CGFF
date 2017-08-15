#include "glShader.h"

namespace CGFF {

	GLShader::GLShader(QString name)
		: m_name(name)
		, m_vertexFile("")
		, m_fragmentFile("")
		, m_vertexSource("")
		, m_fragmentSource("")
	{
	}
	GLShader::~GLShader()
	{
	}

	void GLShader::createFromFile(QString vertexFile, QString fragmentFile)
	{
		m_glShaderProgram.removeAllShaders();
		m_vertexFile = vertexFile;
		m_fragmentFile = fragmentFile;
		load(true);
		init();
	}

	void GLShader::createFromSource(QString vertexSource, QString fragmentSource)
	{
		m_glShaderProgram.removeAllShaders();
		m_vertexSource = vertexSource;
		m_fragmentSource = fragmentSource;
		load(false);
		init();
	}

	void GLShader::init()
	{
		m_VSUserUniformBuffer = nullptr;
		m_PSUserUniformBuffer = nullptr;

		resolveUniforms();
	}

	void GLShader::close()
	{
		m_glShaderProgram.removeAllShaders();
		m_vertexFile = "";
		m_fragmentFile = "";
		m_vertexSource = "";
		m_fragmentSource = "";
	}

	void GLShader::bind()
	{
		m_glShaderProgram.bind();
		s_currentlyBound = this;
	}

	void GLShader::unBind()
	{
		m_glShaderProgram.release();
		s_currentlyBound = nullptr;
	}

	void GLShader::setVSSystemUniformBuffer(uchar* data, uint size, uint slot)
	{
	}

	void GLShader::setPSSystemUniformBuffer(uchar* data, uint size, uint slot)
	{
	}

	void GLShader::setVSUserUniformBuffer(uchar* data, uint size)
	{
	}

	void GLShader::setPSUserUniformBuffer(uchar* data, uint size)
	{
	}

	void GLShader::setUniform(const QString& name, uchar* data)
	{
	}

	void GLShader::resolveAndSetUniformField(const QSharedPointer<ShaderUniformDeclaration>& field, uchar* data, int offset)
	{
	}

	void GLShader::load(bool isFromFile)
	{
		if (isFromFile)
		{
			if (!m_glShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, m_vertexFile))
				qFatal("Error:Can't compile vertex shader");
			if (!m_glShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, m_fragmentFile))
				qFatal("Error:Can't compile vertex shader");
			if (!m_glShaderProgram.link())
				qFatal("Error:Can't link shaders");
		}
		else
		{
			if (!m_glShaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, m_vertexSource))
				qFatal("Error:Can't compile vertex shader");
			if (!m_glShaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, m_fragmentSource))
				qFatal("Error:Can't compile vertex shader");
			if (!m_glShaderProgram.link())
				qFatal("Error:Can't link shaders");
		}
	}

	QSharedPointer<ShaderUniformBufferDeclaration> GLShader::findUniformDeclaration(const QString& name, QSharedPointer<ShaderUniformBufferDeclaration> buffer)
	{
		const ShaderUniformList& uniforms = buffer->getUniformDeclarations();
		for (uint i = 0; i < uniforms.size(); i++)
		{
			if (uniforms[i]->getName() == name)
				return uniforms[i];
		}
		return nullptr;
	}

	QSharedPointer<ShaderUniformBufferDeclaration> GLShader::findUniformDeclaration(const QString& name)
	{
		QSharedPointer<ShaderUniformBufferDeclaration> result = nullptr;
		for (uint i = 0; i < m_VSUniformBuffers.size(); i++)
		{
			result = findUniformDeclaration(name, m_VSUniformBuffers[i]);
			if (result)
				return result;
		}

		for (uint i = 0; i < m_PSUniformBuffers.size(); i++)
		{
			result = findUniformDeclaration(name, m_PSUniformBuffers[i]);
			if (result)
				return result;
		}

		result = findUniformDeclaration(name, m_VSUserUniformBuffer);
		if (result)
			return result;

		result = findUniformDeclaration(name, m_PSUserUniformBuffer);
		if (result)
			return result;

		return result;
	}

	void GLShader::resolveAndSetUniforms(QSharedPointer<ShaderUniformBufferDeclaration> buffer, uchar* data, uint size)
	{
		const ShaderUniformList& uniforms = buffer->getUniformDeclarations();
		for (uint i = 0; i < uniforms.size(); i++)
		{
			QSharedPointer<GLShaderUniformDeclaration> uniform = uniforms[i];
			resolveAndSetUniform(uniform, data, size);
		}
	}

	void GLShader::resolveAndSetUniform(QSharedPointer<GLShaderUniformDeclaration> uniform, uchar* data, uint size) 
	{
		if (uniform->getLocation() == -1)
			return;

		uint offset = uniform->getOffset();

		switch (uniform->getType())
		{
		case GLShaderUniformDeclaration::Type::GLfloat:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(GLfloat *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::GLint:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(GLint *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::GLuint:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(GLuint *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QVector2D:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QVector2D *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QVector3D:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QVector3D *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QVector4D:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QVector4D *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix2x2:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix2x2 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix2x3:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix2x3 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix2x4:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix2x4 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix3x2:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix3x2 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix3x3:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix3x3 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix3x4:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix3x4 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix4x2:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix4x2 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix4x3:
		{
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix4x3 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::QMatrix4x4:
		{
			QMatrix4x4 test = *(QMatrix4x4 *)&data[offset];
			m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix4x4 *)&data[offset]);
			break;
		}
		case GLShaderUniformDeclaration::Type::STRUCT:
			setUniformStruct(uniform, data, offset);
			break;
		default:
			qFatal("Unknown uniform type!");
		}
	}

	void GLShader::setUniformStruct(QSharedPointer<GLShaderUniformDeclaration> uniform, uchar* data, int offset)
	{
		const ShaderStruct& s = uniform->getShaderUniformStruct();
		const auto& fields = s.getFields();
		for (uint k = 0; k < fields.size(); k++)
		{
			QSharedPointer<ShaderUniformDeclaration> field = fields[k];
			resolveAndSetUniformField(field, data, offset);
			offset += field->getSize();
		}
	}

	QSharedPointer<ShaderStruct> GLShader::findStruct(const QString& name)
	{
		for (QSharedPointer<ShaderStruct> s : m_structs)
		{
			if (s->getName() == name)
				return s;
		}
		return nullptr;
	}

	void GLShader::resolveUniforms()
	{

	}
}