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
	}

	void GLShader::createFromSource(QString vertexSource, QString fragmentSource)
	{
		m_glShaderProgram.removeAllShaders();
		m_vertexSource = vertexSource;
		m_fragmentSource = fragmentSource;
		load(false);
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
	}

	void GLShader::unBind()
	{
		m_glShaderProgram.release();
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

}