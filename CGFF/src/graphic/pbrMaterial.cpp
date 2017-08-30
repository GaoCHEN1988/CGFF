#include "pbrMaterial.h"

namespace CGFF {

	QSharedPointer<Texture2D> PBRMaterial::s_preintegratedFG = nullptr;

	PBRMaterial::PBRMaterial(QSharedPointer<Shader> shader)
		: Material(shader)
	{
		if (s_preintegratedFG == nullptr)
			s_preintegratedFG = Texture2D::createFromFile("PreintegratedFG", "Resources/pbr/PreintegratedFG.bmp"); // TODO: Embed into engine!
	
		setTexture("u_PreintegratedFG", s_preintegratedFG);
		setUniform("u_UsingNormalMap", 0.0f);

		// Default parameters for PBR material
		setUniform("u_UsingAlbedoMap", 0.0f);
		setUniform("u_AlbedoColor", QVector4D(0.0f, 0.0f, 0.0f, 1.0f));
		
		setUniform("u_SpecularColor", QVector3D(1.0f, 1.0f, 1.0f));
		setUniform("u_UsingSpecularMap", 0.0f);
		
		setUniform("u_GlossColor", 0.8f);
		setUniform("u_UsingGlossMap", 0.0f);
		
		setUniform("u_UsingNormalMap", 0.0f);
	}

	PBRMaterial::~PBRMaterial()
	{
		s_preintegratedFG.clear();
	}

	void PBRMaterial::setEnviromentMap(QSharedPointer<TextureCube> texture)
	{
		setTexture("u_EnvironmentMap", texture);
	}

	// PBR Statics
	void PBRMaterial::setAlbedo(const QVector4D& color)
	{
		setUniform("u_AlbedoColor", color);
		setUniform("u_UsingAlbedoMap", 0.0f);
	}

	void PBRMaterial::setSpecular(const QVector3D& color)
	{
		setUniform("u_SpecularColor", color);
		setUniform("u_UsingSpecularMap", 0.0f);
	}

	void PBRMaterial::setGloss(float value)
	{
		setUniform("u_GlossColor", value);
		setUniform("u_UsingGlossMap", 0.0f);
	}

	void PBRMaterial::usingNormalMap(bool value)
	{
		setUniform("u_UsingNormalMap", value ? 1.0f : 0.0f);
	}

	// PBR Maps
	void PBRMaterial::setAlbedoMap(QSharedPointer<Texture2D> texture)
	{
		setTexture("u_AlbedoMap", texture);
		setUniform("u_UsingAlbedoMap", 1.0f);
	}

	void PBRMaterial::setSpecularMap(QSharedPointer<Texture2D> texture)
	{
		setTexture("u_SpecularMap", texture);
		setUniform("u_UsingSpecularMap", 1.0f);
	}

	void PBRMaterial::setNormalMap(QSharedPointer<Texture2D> texture)
	{
		setTexture("u_NormalMap", texture);
		setUniform("u_UsingNormalMap", 1.0f);
	}

	void PBRMaterial::setGlossMap(QSharedPointer<Texture2D> texture)
	{
		setTexture("u_GlossMap", texture);
		setUniform("u_UsingGlossMap", 1.0f);
	}

	QSharedPointer<Texture> PBRMaterial::getAlbedoMap()
	{
		QSharedPointer<ShaderResourceDeclaration> declaration = findResourceDeclaration("u_AlbedoMap");
		Q_ASSERT(!declaration.isNull());
		uint slot = declaration->getRegister();
		return m_textures.size() > slot ? m_textures[slot] : nullptr;
	}

	QSharedPointer<Texture> PBRMaterial::getSpecularMap()
	{
		QSharedPointer<ShaderResourceDeclaration> declaration = findResourceDeclaration("u_SpecularMap");
		Q_ASSERT(!declaration.isNull());
		uint slot = declaration->getRegister();
		return m_textures.size() > slot ? m_textures[slot] : nullptr;
	}

	QSharedPointer<Texture> PBRMaterial::getNormalMap()
	{
		QSharedPointer<ShaderResourceDeclaration> declaration = findResourceDeclaration("u_NormalMap");
		Q_ASSERT(!declaration.isNull());
		uint slot = declaration->getRegister();
		return m_textures.size() > slot ? m_textures[slot] : nullptr;
	}

	QSharedPointer<Texture> PBRMaterial::getGlossMap()
	{
		QSharedPointer<ShaderResourceDeclaration> declaration = findResourceDeclaration("u_GlossMap");
		Q_ASSERT(!declaration.isNull());
		uint slot = declaration->getRegister();
		return m_textures.size() > slot ? m_textures[slot] : nullptr;
	}

	//-------------------------------------------------------------------------------------

	PBRMaterialInstance::PBRMaterialInstance(QSharedPointer<PBRMaterial> material)
		: MaterialInstance(material)
	{
	}

	void PBRMaterialInstance::setEnviromentMap(QSharedPointer<TextureCube> texture)
	{
		setTexture("u_EnvironmentMap", texture);
	}

	// PBR Statics
	void PBRMaterialInstance::setAlbedo(const QVector4D& color)
	{
		setUniform("u_AlbedoColor", color);
		setUniform("u_UsingAlbedoMap", 0.0f);
	}
	void PBRMaterialInstance::setSpecular(const QVector3D& color)
	{
		setUniform("u_SpecularColor", color);
		setUniform("u_UsingSpecularMap", 0.0f);
	}
	void PBRMaterialInstance::setGloss(float value)
	{
		setUniform("u_GlossColor", value);
		setUniform("u_UsingGlossMap", 0.0f);
	}

	void PBRMaterialInstance::usingNormalMap(bool value)
	{
		setUniform("u_UsingNormalMap", value ? 1.0f : 0.0f);
	}

	void PBRMaterialInstance::setAlbedoMap(QSharedPointer<Texture2D> texture)
	{
		setTexture("u_AlbedoMap", texture);
		setUniform("u_UsingAlbedoMap", 1.0f);
	}
	void PBRMaterialInstance::setSpecularMap(QSharedPointer<Texture2D> texture)
	{
		setTexture("u_SpecularMap", texture);
		setUniform("u_UsingSpecularMap", 1.0f);
	}
	void PBRMaterialInstance::setNormalMap(QSharedPointer<Texture2D> texture)
	{
		setTexture("u_NormalMap", texture);
		setUniform("u_UsingNormalMap", 1.0f);
	}
	void PBRMaterialInstance::setGlossMap(QSharedPointer<Texture2D> texture)
	{
		setUniform("u_GlossMap", texture);
		setUniform("u_UsingGlossMap", 1.0f);
	}

}