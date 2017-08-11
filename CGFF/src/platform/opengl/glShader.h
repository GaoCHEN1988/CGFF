#ifndef CGFF_GL_SHADER_H
#define CGFF_GL_SHADER_H

#include "graphic/shader/shader.h"
#include <QOpenGLShaderProgram>

namespace CGFF {

	class GLShader : public Shader
	{
	public:
		GLShader(QString name);
		virtual ~GLShader();

		void createFromFile(QString vertexFile, QString fragmentFile);
		void createFromSource(QString vertexSource, QString fragmentSource);

		void close() override;
		void bind() override;
		void unBind() override;
		inline QString getName() const override
		{
			return m_name;
		};

	private:
		friend class Shader;
		friend class ShaderManager;
		void load(bool isFromFile);

	private:
		QOpenGLShaderProgram m_glShaderProgram;
		QString m_name;
		QString m_vertexFile;
		QString m_vertexSource;
		QString m_fragmentFile;
		QString m_fragmentSource;

	};
}

#endif