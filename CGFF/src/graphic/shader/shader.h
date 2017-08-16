#ifndef CGFF_SHADER_H
#define CGFF_SHADER_H

#include "utils/qtopengl.h"
#include "shaderUniform.h"
#include "shaderResource.h"

namespace CGFF {

#define SHADER_VERTEX_INDEX     0
#define SHADER_UV_INDEX         1
#define SHADER_MASK_UV_INDEX	2
#define SHADER_TID_INDEX        3
#define SHADER_MID_INDEX        4
#define SHADER_COLOR_INDEX      5

#define SHADER_UNIFORM_PROJECTION_MATRIX_NAME	"pr_matrix"
#define SHADER_UNIFORM_VIEW_MATRIX_NAME			"vw_matrix"
#define SHADER_UNIFORM_MODEL_MATRIX_NAME		"ml_matrix"
#define SHADER_UNIFORM_LIGHT_POSITION		    "u_LightPosition"
#define SHADER_UNIFORM_LIGHT_ATTENUATION		"u_LightAttenuation"
#define SHADER_UNIFORM_LIGHT_COLOR		        "u_LightColor"

	class Shader
	{
	public:
		virtual void bind() = 0;
		virtual void unBind() = 0;
		virtual void close() = 0;
		virtual void reload() = 0;

		virtual void setVSSystemUniformBuffer(uchar* data, uint size, uint slot = 0) = 0;
		virtual void setPSSystemUniformBuffer(uchar* data, uint size, uint slot = 0) = 0;

		virtual void setVSUserUniformBuffer(uchar* data, uint size) = 0;
		virtual void setPSUserUniformBuffer(uchar* data, uint size) = 0;

		virtual const ShaderUniformBufferList& getVSSystemUniforms() const = 0;
		virtual const ShaderUniformBufferList& getPSSystemUniforms() const = 0;
		virtual const QSharedPointer<ShaderUniformBufferDeclaration> getVSUserUniformBuffer() const = 0;
		virtual const QSharedPointer<ShaderUniformBufferDeclaration> getPSUserUniformBuffer() const = 0;

		virtual const ShaderResourceList& getResources() const = 0;

		virtual QString getName() const = 0;
		//virtual QString getFilePath() const = 0;

		// virtual void SetData(uchar* data, uint size) = 0;

		// bool HasUniform(const String& name) const = 0;
	public:
		static QSharedPointer<Shader> createFromFile(const QString& name, const QString& vertexFile, const QString& fragmentFile);
		static QSharedPointer<Shader> createFromSource(const QString& name, const QString& vertexSource, const QString& fragmentSource);

	public:
		static const Shader* s_currentlyBound;
	};
}

#endif