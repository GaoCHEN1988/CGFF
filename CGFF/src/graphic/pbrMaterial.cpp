#include "pbrMaterial.h"

namespace CGFF {

	PBRMaterial::PBRMaterial(QSharedPointer<Shader> shader){}
	PBRMaterial::~PBRMaterial(){}

	void PBRMaterial::setEnviromentMap(QSharedPointer<TextureCube> texture)
	{
	}

	// PBR Statics
	void PBRMaterial::setAlbedo(const QVector4D& color){}
	void PBRMaterial::setSpecular(const QVector3D& color){}
	void PBRMaterial::setGloss(float value){}
	void PBRMaterial::usingNormalMap(bool value){}

	// PBR Maps
	void PBRMaterial::setAlbedoMap(QSharedPointer<Texture2D> texture){}
	void PBRMaterial::setSpecularMap(QSharedPointer<Texture2D> texture){}
	void PBRMaterial::setNormalMap(QSharedPointer<Texture2D> texture){}
	void PBRMaterial::setGlossMap(QSharedPointer<Texture2D> texture){} // TODO: Grayscale texture

	QSharedPointer<Texture> PBRMaterial::getAlbedoMap(){}
	QSharedPointer<Texture> PBRMaterial::getSpecularMap(){}
	QSharedPointer<Texture> PBRMaterial::getNormalMap(){}
	QSharedPointer<Texture> PBRMaterial::getGlossMap(){}

	//-------------------------------------------------------------------------------------

	PBRMaterialInstance::PBRMaterialInstance(PBRMaterial* material){}

	void PBRMaterialInstance::setEnviromentMap(QSharedPointer<TextureCube> texture){}

	// PBR Statics
	void PBRMaterialInstance::setAlbedo(const QVector4D& color){}
	void PBRMaterialInstance::setSpecular(const QVector3D& color){}
	void PBRMaterialInstance::setGloss(float value){}
	void PBRMaterialInstance::usingNormalMap(bool value){}

	// PBR Maps
	void PBRMaterialInstance::setAlbedoMap(QSharedPointer<Texture2D> texture){}
	void PBRMaterialInstance::setSpecularMap(QSharedPointer<Texture2D> texture){}
	void PBRMaterialInstance::setNormalMap(QSharedPointer<Texture2D> texture){}
	void PBRMaterialInstance::setGlossMap(QSharedPointer<Texture2D> texture){} // TODO: Grayscale texture

}