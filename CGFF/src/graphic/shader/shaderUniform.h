#ifndef CGFF_SHADER_UNIFORM_H
#define CGFF_SHADER_UNIFORM_H

#include "shaderProgram.h"

namespace CGFF {

	class ShaderUniformDeclaration
	{

	public:
		virtual QString getName() const = 0;
		virtual int getSize() const = 0;
		virtual int getCount() const = 0;
		virtual int getOffset() const = 0;

	private:
		friend class ShaderProgram;
		friend class ShaderStruct;

	protected:
		virtual void setOffset(int offset) = 0;
	};

	typedef QVector<QSharedPointer<ShaderUniformDeclaration>> ShaderUniformList;

	class ShaderUniformBufferDeclaration
	{
	public:
		virtual QString getName() const = 0;
		virtual int getRegister() const = 0;
		virtual int getShaderType() const = 0;
		virtual int getSize() const = 0;
		virtual const ShaderUniformList& getUniformDeclarations() const = 0;

		virtual QSharedPointer<ShaderUniformDeclaration> findUniform(const QString& name) = 0;
	};

	typedef QVector<QSharedPointer<ShaderUniformBufferDeclaration>> ShaderUniformBufferList;

	class ShaderStruct
	{
	private:
		friend class Shader;
	private:
		QString m_name;
		QVector<QSharedPointer<ShaderUniformDeclaration>> m_fields;
		int m_size;
		int m_offset;
	public:
		ShaderStruct(const QString& name)
			: m_name(name)
			, m_size(0)
			, m_offset(0)
		{
		}

		void AddField(QSharedPointer<ShaderUniformDeclaration> field)
		{
			m_size += field->getSize();
			int offset = 0;
			if (m_fields.size())
			{
				QSharedPointer<ShaderUniformDeclaration> previous = m_fields.back();
				offset = previous->getOffset() + previous->getSize();
			}
			field->setOffset(offset);
			m_fields.push_back(field);
		}

		inline void setOffset(int offset) { m_offset = offset; }

		inline QString getName() const { return m_name; }
		inline int getSize() const { return m_size; }
		inline int getOffset() const { return m_offset; }
		inline const QVector<QSharedPointer<ShaderUniformDeclaration>>& getFields() const { return m_fields; }
	};

	typedef QVector<QSharedPointer<ShaderStruct>> ShaderStructList;
}

#endif