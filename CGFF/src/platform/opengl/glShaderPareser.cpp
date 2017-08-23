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

	//QStringList GLShaderParser::findToken(const QString& source, QString token)
	//{
	//	QStringList result;

	//	QString t = "("+token + ".+?" + ";)";
	//	QRegularExpression reg(t);

	//	QRegularExpressionMatchIterator i = reg.globalMatch(source);

	//	while (i.hasNext()) {
	//		QRegularExpressionMatch match = i.next();
	//		if (match.hasMatch()) {
	//			result.append(match.captured(0));
	//		}
	//	}

	//	return result;
	//}

	QStringList GLShaderParser::findUniforms(const QString& source)
	{
		QStringList result;

		QString t = "(uniform.+?;)";
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

	QStringList GLShaderParser::findStructs(const QString& source)
	{
		QStringList result;

		QString t = "(struct(.|\n)+?})";
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
			outName.remove(QRegularExpression("\\[(\\d+)\\]"));
		}
	}

	QStringList  GLShaderParser::seperateStructStatement(const QString& statement, QString& outName)
	{
		QStringList result;

		QRegularExpression regName("struct\\s+(.+?)\\s+|\n");

		QRegularExpressionMatch match = regName.match(statement);

		outName = "";

		if (match.hasMatch())
		{
			outName = match.captured(1);
		}

		QRegularExpression reg("\\{((.|\n)+?)\\}");

		match = reg.match(statement);
		//Test
		if (match.hasMatch())
		{
			QString tmp = match.captured(1);
			QString t = "(.+?;)";
			QRegularExpressionMatchIterator i = reg.globalMatch(tmp);

			result = tmp.split(QRegularExpression(";"));

			result.removeLast();
		}

		return result;
	}
}