#ifndef CGFF_MATERIAL_H
#define CGFF_MATERIAL_H

#include "utils/qtopengl.h"
#include "utils/types.h"
#include "shader/shader.h"
#include "api/texture2D.h"
#include "api/textureCube.h"
#include "common.h"

//#include <QByteArray>
//#include <QDataStream>


namespace CGFF {

#define IMPLEMENT_MATERIAL_SET_UNIFORM(Type)  template<>\
    inline void Material::setUniform<Type>(const char * name, const Type& value)\
    {\
        int index = m_shader->uniformLocation(name);\
        if (-1 == index)\
        {\
            qFatal("Could not find uniform %s", name);\
        }\
        UniformData uniform_data;\
        uniform_data.type = UniformType::Type;\
        uniform_data.data_pointer = QSharedPointer<char>(new char[sizeof(Type)]);\
        memcpy(uniform_data.data_pointer.data(), &value, sizeof(Type));\
        m_uniformDatas[index] = uniform_data;\
    }\

#define IMPLEMENT_MATERIALINSTANCE_SET_UNIFORM(Type)  template<>\
    inline void MaterialInstance::setUniform<Type>(const char * name, const Type& value)\
    {\
        int index = m_material->getShader()->uniformLocation(name);\
        if (-1 == index)\
        {\
            qFatal("Could not find uniform %s", name);\
        }\
        UniformData uniform_data;\
        uniform_data.type = UniformType::Type;\
        uniform_data.data_pointer = QSharedPointer<char>(new char[sizeof(Type)]);\
        memcpy(uniform_data.data_pointer.data(), &value, sizeof(Type));\
        m_uniformDatas[index] = uniform_data;\
    }\

#define IMPLEMENT_SET_UNIFORM(type) IMPLEMENT_MATERIAL_SET_UNIFORM(type)\
    IMPLEMENT_MATERIALINSTANCE_SET_UNIFORM(type)

    class Material
    {
	public:
		enum class RenderFlags
		{
			NONE = 0,
			DISABLE_DEPTH_TEST = BIT(0),
			WIREFRAME = BIT(1)
		};

    public:
        Material(QSharedPointer<Shader> shader);
        virtual ~Material();

        void bind() const;
        void unbind() const;

        QSharedPointer<Shader> getShader();

		void setUniformData(const QString& uniform, uchar* data);
		void setTexture(const QString& name, QSharedPointer<Texture> texture);

		inline int getRenderFlags() const { return m_renderFlags; }
		void setRenderFlags(int flags) { m_renderFlags = flags; }
		void setRenderFlag(Material::RenderFlags flag) { m_renderFlags |= (int)flag; }

        //template<typename T>
        //void setUniform(const char *name, const T& value)
        //{
        //    qFatal("Unknown uniform type!");
        //}

		template<typename T>
		void setUniform(const QString& name, const T& data)
		{
			QSharedPointer<uchar> buffer;
			QSharedPointer<ShaderUniformDeclaration> declaration = findUniformDeclaration(name, buffer);
			if (declaration.isNull())
			{
				qFatal("Could not find uniform with name '", name, "'!");
				return;
			}
			memcpy(buffer.data() + declaration->getOffset(), &data, declaration->getSize());
		}

		//template<typename T>
		//const T* getUniform(const String& name) const
		//{
		//	return getUniform<T>(getUniformDeclaration(name));
		//}

		//template<typename T>
		//const T* getUniform(const API::ShaderUniformDeclaration* uniform) const
		//{
		//	return (T*)&m_UniformData[uniform->GetOffset()];
		//}

	protected:
		void allocateStorage();
		QSharedPointer<ShaderUniformDeclaration> findUniformDeclaration(const QString& name, QSharedPointer<uchar>& outBuffer);
		QSharedPointer<ShaderResourceDeclaration> findResourceDeclaration(const QString& name);

	private:
		friend class MaterialInstance;

	protected:
		QSharedPointer<Shader> m_shader;
		QSharedPointer<uchar> m_VSUserUniformBuffer;
		uint m_VSUserUniformBufferSize;
		QSharedPointer<uchar> m_PSUserUniformBuffer;
		uint m_PSUserUniformBufferSize;
		QVector<QSharedPointer<Texture>> m_textures;
		const ShaderUniformList* m_VSUserUniforms;
		const ShaderUniformList* m_PSUserUniforms;
		const ShaderResourceList* m_resources;

		int m_renderFlags;
    };

    class MaterialInstance
    {
    public:

        MaterialInstance(QSharedPointer<Material> material);
        void bind();
        void unbind();

        inline QSharedPointer<Material>& getMaterial() { return m_material; }

		void setUniformData(const QString& uniform, uchar* data);
		void setTexture(const QString& name, QSharedPointer<Texture> texture);

		inline int getRenderFlags() const { return m_renderFlags; }
		void setRenderFlags(int flags) { m_renderFlags = flags; }
		void setRenderFlag(Material::RenderFlags flag) { m_renderFlags |= (int)flag; }

		template<typename T>
		void setUniform(const QString& name, const T& data)
		{
			QSharedPointer<uchar> buffer;
			QSharedPointer<ShaderUniformDeclaration> declaration = findUniformDeclaration(name, buffer);
			Q_ASSERT(!declaration.isNull());
			memcpy(buffer.data() + declaration->getOffset(), &data, declaration->getSize());
		}

		//template<typename T>
		//const T* getUniform(const String& name) const
		//{
		//	return getUniform<T>(getUniformDeclaration(name));
		//}

        //template<typename T>
        //void setUniform(const char * name, const T& value)
        //{
        //    qFatal("Unknown uniform type!");
        //}
        //void setRendererUniform(const RendererUniform& uniform);
        //void unsetUniform(const QString& name, bool unset);

	private:
		void allocateStorage();
		QSharedPointer<ShaderUniformDeclaration> findUniformDeclaration(const QString& name, QSharedPointer<uchar>& outBuffer);
		QSharedPointer<ShaderResourceDeclaration> findResourceDeclaration(const QString& name);
    private:
        QSharedPointer<Material> m_material;
        QHash<int, UniformData> m_uniformDatas;
        QHash<int, RendererUniform> m_rUniformDatas;
        QHash<int, bool> m_unsetUniformMap;
        bool m_isRendererData;

		QSharedPointer<uchar> m_VSUserUniformBuffer;
		uint m_VSUserUniformBufferSize;
		QSharedPointer<uchar> m_PSUserUniformBuffer;
		uint m_PSUserUniformBufferSize;
		QVector<QSharedPointer<Texture>> m_textures;

		const ShaderUniformList* m_VSUserUniforms;
		const ShaderUniformList* m_PSUserUniforms;
		const ShaderResourceList* m_resources;

		int m_renderFlags;
    };

    //IMPLEMENT_SET_UNIFORM(GLfloat)
    //IMPLEMENT_SET_UNIFORM(GLint)
    //IMPLEMENT_SET_UNIFORM(GLuint)
    //IMPLEMENT_SET_UNIFORM(QVector2D)
    //IMPLEMENT_SET_UNIFORM(QVector3D)
    //IMPLEMENT_SET_UNIFORM(QVector4D)
    //IMPLEMENT_SET_UNIFORM(QMatrix2x2)
    //IMPLEMENT_SET_UNIFORM(QMatrix2x3)
    //IMPLEMENT_SET_UNIFORM(QMatrix2x4)
    //IMPLEMENT_SET_UNIFORM(QMatrix3x2)
    //IMPLEMENT_SET_UNIFORM(QMatrix3x3)
    //IMPLEMENT_SET_UNIFORM(QMatrix3x4)
    //IMPLEMENT_SET_UNIFORM(QMatrix4x2)
    //IMPLEMENT_SET_UNIFORM(QMatrix4x3)
    //IMPLEMENT_SET_UNIFORM(QMatrix4x4)
}

#endif
