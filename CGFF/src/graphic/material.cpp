#include "material.h"

namespace CGFF {

    Material::Material(QSharedPointer<Shader> shader)
        : m_shader(shader)
		, m_renderFlags(0)
    {
		allocateStorage();
		m_resources = &shader->getResources();
    }

    Material::~Material()
    {
		m_textures.clear();
    }

    void Material::bind() const
    {
		m_shader->bind();
		// TODO: Don't do this if a MaterialInstance is being used
		//if (!m_VSUserUniformBuffer.isNull())
		//	m_shader->setVSUserUniformBuffer(m_VSUserUniformBuffer.data(), m_VSUserUniformBufferSize);
		//if (!m_PSUserUniformBuffer.isNull())
		//	m_shader->setPSUserUniformBuffer(m_PSUserUniformBuffer.data(), m_PSUserUniformBufferSize);

		//for (uint i = 0; i < m_textures.size(); i++)
		//{
		//	QSharedPointer<Texture> texture = m_textures[i];
		//	if (!texture.isNull())
		//		texture->bind(i);
		//}

    }
    void Material::unbind() const
    {
        m_shader->unBind();

		for (uint i = 0; i < m_textures.size(); i++)
		{
			QSharedPointer<Texture> texture = m_textures[i];
			if (!texture.isNull())
				texture->unBind(i);
		}
    }

    QSharedPointer<Shader> Material::getShader()
    {
        return m_shader;
    }

	void Material::setUniformData(const QString& uniform, uchar* data)
	{
		QSharedPointer<uchar> buffer;
		QSharedPointer<ShaderUniformDeclaration> declaration = findUniformDeclaration(uniform, buffer);
		memcpy(buffer.data() + declaration->getOffset(), data, declaration->getSize());
	}

	void Material::setTexture(const QString& name, QSharedPointer<Texture> texture)
	{
		QSharedPointer<ShaderResourceDeclaration> declaration = findResourceDeclaration(name);
		Q_ASSERT(!declaration.isNull());
		uint slot = declaration->getRegister();

		if (m_textures.size() <= slot)
			m_textures.resize(slot + 1);

		m_textures[slot] = texture;
	}

	void Material::allocateStorage()
	{
		m_VSUserUniformBuffer = nullptr;
		m_VSUserUniformBufferSize = 0;

		m_PSUserUniformBuffer = nullptr;
		m_PSUserUniformBufferSize = 0;

		m_VSUserUniforms = nullptr;
		m_PSUserUniforms = nullptr;

		const QSharedPointer<ShaderUniformBufferDeclaration> vsBuffer = m_shader->getVSUserUniformBuffer();
		if (vsBuffer)
		{
			m_VSUserUniformBufferSize = vsBuffer->getSize();
			m_VSUserUniformBuffer = QSharedPointer<uchar>(new uchar[m_VSUserUniformBufferSize]);
			memset(m_VSUserUniformBuffer.data(), 0, m_VSUserUniformBufferSize);
			m_VSUserUniforms = &vsBuffer->getUniformDeclarations();
		}

		const  QSharedPointer<ShaderUniformBufferDeclaration> psBuffer = m_shader->getPSUserUniformBuffer();
		if (psBuffer)
		{
			m_PSUserUniformBufferSize = psBuffer->getSize();
			m_PSUserUniformBuffer = QSharedPointer<uchar>(new uchar[m_PSUserUniformBufferSize]);
			memset(m_PSUserUniformBuffer.data(), 0, m_PSUserUniformBufferSize);
			m_PSUserUniforms = &psBuffer->getUniformDeclarations();
		}
	}

	QSharedPointer<ShaderUniformDeclaration> Material::findUniformDeclaration(const QString& name, QSharedPointer<uchar>& outBuffer)
	{
		if (m_VSUserUniforms)
		{
			for (QSharedPointer<ShaderUniformDeclaration> uniform : *m_VSUserUniforms)
			{
				if (uniform->getName() == name)
				{
					outBuffer = m_VSUserUniformBuffer;
					return uniform;
				}
			}
		}
		if (m_PSUserUniforms)
		{
			for (QSharedPointer<ShaderUniformDeclaration> uniform : *m_PSUserUniforms)
			{
				if (uniform->getName() == name)
				{
					outBuffer = m_PSUserUniformBuffer;
					return uniform;
				}
			}
		}
		return nullptr;
	}

	QSharedPointer<ShaderResourceDeclaration> Material::findResourceDeclaration(const QString& name)
	{
		for (QSharedPointer<ShaderResourceDeclaration> resource : *m_resources)
		{
			if (resource->getName() == name)
				return resource;
		}
		return nullptr;
	}


	//-------------------------------------------------------------------------------------

    MaterialInstance::MaterialInstance(QSharedPointer<Material> material)
        : m_material(material)
        , m_isRendererData(true)
		, m_renderFlags(0)
    {
		allocateStorage();

		memcpy(m_VSUserUniformBuffer.data(), m_material->m_VSUserUniformBuffer.data(), m_VSUserUniformBufferSize);
		memcpy(m_PSUserUniformBuffer.data(), m_material->m_PSUserUniformBuffer.data(), m_PSUserUniformBufferSize);

		m_resources = &m_material->getShader()->getResources();
		m_renderFlags = material->m_renderFlags;
    }

	MaterialInstance::~MaterialInstance()
	{
		m_textures.clear();
	}

    void MaterialInstance::bind()
    {
        m_material->bind();
        if (m_VSUserUniformBuffer)
            m_material->m_shader->setVSUserUniformBuffer(m_VSUserUniformBuffer.data(), m_VSUserUniformBufferSize);
        if (m_PSUserUniformBuffer)
            m_material->m_shader->setPSUserUniformBuffer(m_PSUserUniformBuffer.data(), m_PSUserUniformBufferSize);

        for (uint i = 0; i < m_textures.size(); i++)
        {
            QSharedPointer<Texture> texture = m_textures[i];
            if (!texture.isNull())
                texture->bind(i);
        }
    }

    void MaterialInstance::unbind()
    {
        m_material->unbind();

        for (uint i = 0; i < m_textures.size(); i++)
        {
            QSharedPointer<Texture> texture = m_textures[i];
            if (!texture.isNull())
                texture->unBind(i);
        }
    }


	void MaterialInstance::setUniformData(const QString& uniform, uchar* data)
	{
		QSharedPointer<uchar> buffer;
		QSharedPointer<ShaderUniformDeclaration> declaration = findUniformDeclaration(uniform, buffer);
		Q_ASSERT(!buffer.isNull());
		memcpy(buffer.data() + declaration->getOffset(), data, declaration->getSize());
	}

	void MaterialInstance::setTexture(const QString& name, QSharedPointer<Texture> texture)
	{
		QSharedPointer<ShaderResourceDeclaration> declaration = findResourceDeclaration(name);
		uint slot = declaration->getRegister();

		if (m_textures.size() <= slot)
			m_textures.resize(slot + 1);

		m_textures[slot] = texture;
	}

	void MaterialInstance::allocateStorage()
	{
		m_VSUserUniformBuffer = nullptr;
		m_VSUserUniformBufferSize = 0;

		m_PSUserUniformBuffer = nullptr;
		m_PSUserUniformBufferSize = 0;

		m_VSUserUniforms = nullptr;
		m_PSUserUniforms = nullptr;

		const QSharedPointer<ShaderUniformBufferDeclaration> vsBuffer = m_material->m_shader->getVSUserUniformBuffer();
		if (!vsBuffer.isNull())
		{
			m_VSUserUniformBufferSize = vsBuffer->getSize();
			m_VSUserUniformBuffer = QSharedPointer<uchar>(new uchar[m_VSUserUniformBufferSize]);
			m_VSUserUniforms = &vsBuffer->getUniformDeclarations();
		}

		const QSharedPointer<ShaderUniformBufferDeclaration> psBuffer = m_material->m_shader->getPSUserUniformBuffer();
		if (!psBuffer.isNull())
		{
			m_PSUserUniformBufferSize = psBuffer->getSize();
			m_PSUserUniformBuffer = QSharedPointer<uchar>(new uchar[m_PSUserUniformBufferSize]);
			m_PSUserUniforms = &psBuffer->getUniformDeclarations();
		}
	}

	QSharedPointer<ShaderUniformDeclaration> MaterialInstance::findUniformDeclaration(const QString& name, QSharedPointer<uchar>& outBuffer)
	{
		if (m_VSUserUniforms)
		{
			for (QSharedPointer<ShaderUniformDeclaration> uniform : *m_VSUserUniforms)
			{
				if (uniform->getName() == name)
				{
					outBuffer = m_VSUserUniformBuffer;
					return uniform;
				}
			}
		}
		if (m_PSUserUniforms)
		{
			for (QSharedPointer<ShaderUniformDeclaration> uniform : *m_PSUserUniforms)
			{
				if (uniform->getName() == name)
				{
					outBuffer = m_PSUserUniformBuffer;
					return uniform;
				}
			}
		}
		return nullptr;
	}

	QSharedPointer<ShaderResourceDeclaration> MaterialInstance::findResourceDeclaration(const QString& name)
	{
		for (QSharedPointer<ShaderResourceDeclaration> resource : *m_resources)
		{
			if (resource->getName() == name)
				return resource;
		}
		return nullptr;
	}
}