#include "glShaderPareser.h"
#include <QRegularExpression>

namespace CGFF {

	GLShaderParser::GLShaderParser(const QString& shaderSource)
		: m_source(shaderSource)
	{

	}

	GLShaderParser::~GLShaderParser()
	{

	}

	void GLShaderParser::setSource(const QString& shaderSource)
	{
		m_source = shaderSource;
	}

	QStringList GLShaderParser::findToken(const QString& source, QString token)
	{
		QStringList result;

		QString t = "("+token + ".+?" + ";)";
		QRegularExpression reg(t);

		QRegularExpressionMatchIterator i = reg.globalMatch(source);

		while (i.hasNext()) {
			QRegularExpressionMatch match = i.next();
			if (match.hasMatch()) {
				result.append(match.captured(0));
			}
		}

		return result;
	}

	void GLShaderParser::seperateTokenStatement(const QString& statement, QString& outType, QString& outName, int& outCount)
	{
		QStringList tokens = statement.split(QRegularExpression("\\s+"));
		int index = 1;
		outType = tokens[index];
		index++;
		outName = tokens[index];
		outName.remove(QRegularExpression("(;)"));

		outCount = 1;
		QRegularExpression regCount("\\[(\\d+)\\]");

		QRegularExpressionMatch match = regCount.match(outName);

		if (match.hasMatch())
		{
			QString sCount = match.captured(1);
			outCount = sCount.toInt();
		}
	}

	QStringList  GLShaderParser::seperateStructStatement(const QString& statement, QString& outName)
	{
		QStringList result;

		QRegularExpression regName("struct\\s+(.+?)\\s+");

		QRegularExpressionMatch match = regName.match(statement);

		outName = "";

		if (match.hasMatch())
		{
			outName = match.captured(0);
		}

		QRegularExpression reg("\\{((.|\n)+?)\\}");

		match = reg.match(statement);

		if (match.hasMatch())
		{
			QString tmp = match.captured(0);
			result.append(tmp);
		}

		return result;
	}
}