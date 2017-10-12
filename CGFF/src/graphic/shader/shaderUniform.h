#ifndef CGFF_SHADER_UNIFORM_H
#define CGFF_SHADER_UNIFORM_H

#include "shaderProgram.h"

namespace CGFF {

	enum class ShaderType
	{
		UNKNOWN,
		VERTEX,
		FRAGMENT, 
        GEOMETRY
	};

	class ShaderUniformDeclaration
	{

	public:
		virtual QString getName() const = 0;
		virtual uint getSize() const = 0;
		virtual uint getCount() const = 0;
		virtual uint getOffset() const = 0;
        virtual QSharedPointer<ShaderUniformDeclaration> deepCopy() = 0;
	private:
		friend class ShaderProgram;
		friend class ShaderStruct;

	protected:
		virtual void setOffset(uint offset) = 0;
	};

	typedef QVector<QSharedPointer<ShaderUniformDeclaration>> ShaderUniformList;

	class ShaderUniformBufferDeclaration
	{
	public:
		virtual QString getName() const = 0;
		virtual uint getRegister() const = 0;
		virtual ShaderType getShaderType() const = 0;
		virtual uint getSize() const = 0;
		virtual const ShaderUniformList& getUniformDeclarations() const = 0;

		virtual QSharedPointer<ShaderUniformDeclaration> findUniform(const QString& name) = 0;
	};

	typedef QVector<QSharedPointer<ShaderUniformBufferDeclaration>> ShaderUniformBufferList;

	class ShaderStruct
	{
	public:
        explicit ShaderStruct(const QString& name);
        explicit ShaderStruct(const ShaderStruct& shaderStruct);

		void addField(QSharedPointer<ShaderUniformDeclaration> field);

		inline void setOffset(int offset) { m_offset = offset; }

		inline QString getName() const { return m_name; }
		inline int getSize() const { return m_size; }
		inline int getOffset() const { return m_offset; }
		inline const QVector<QSharedPointer<ShaderUniformDeclaration>>& getFields() const { return m_fields; }
	
	private:
		friend class Shader;
	private:
		QString m_name;
		QVector<QSharedPointer<ShaderUniformDeclaration>> m_fields;
		int m_size;
		int m_offset;
	
	};

	typedef QVector<QSharedPointer<ShaderStruct>> ShaderStructList;
}

#endif