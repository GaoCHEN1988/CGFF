#ifndef CGFF_GL_SHADER_PARSER_H
#define CGFF_GL_SHADER_PARSER_H

#include <QString>

namespace CGFF {

	class GLShaderParser
	{
	public:
		GLShaderParser(const QString& shaderSource);
		virtual ~GLShaderParser();

		void setSource(const QString& shaderSource);

		//static QStringList findToken(const QString& source, QString token);
		static QStringList findUniforms(const QString& source);
		static QStringList findStructs(const QString& source);
		static void seperateTokenStatement(const QString& statement, QString& outType, QString& outName, int& outCount);
		static QStringList seperateStructStatement(const QString& statement, QString& outName);

	private:
		QString m_source;
	};

}

#endif
