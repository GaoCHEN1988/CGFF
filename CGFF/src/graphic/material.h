#ifndef CGFF_MATERIAL_H
#define CGFF_MATERIAL_H

#include "utils/qtopengl.h"
#include "utils/types.h"
#include "shader/shader.h"
#include "api/texture2D.h"
#include "api/textureCube.h"
#include "common.h"

namespace CGFF {

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
		virtual ~MaterialInstance();
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
            if (declaration.isNull())
                return;
			Q_ASSERT(!declaration.isNull());
			memcpy(buffer.data() + declaration->getOffset(), &data, declaration->getSize());
		}

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
}

#endif
