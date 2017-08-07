#ifndef PBR_MATERIAL_H
#define PBR_MATERIAL_H

#include"material.h"

namespace CGFF {
    class PBRMaterial : public Material
    {
    public:
        PBRMaterial(ShaderProgram* shader);
        ~PBRMaterial();

        void setEnviromentMap(TextureCube* texture);

        // PBR Statics
        void setAlbedo(const QVector4D& color);
        void setSpecular(const QVector3D& color);
        void setGloss(float value);
        void usingNormalMap(bool value);

        // PBR Maps
        void setAlbedoMap(API::Texture2D* texture);
        void setSpecularMap(API::Texture2D* texture);
        void setNormalMap(API::Texture2D* texture);
        void setGlossMap(API::Texture2D* texture); // TODO: Grayscale texture

        API::Texture* GetAlbedoMap();
        API::Texture* GetSpecularMap();
        API::Texture* GetNormalMap();
        API::Texture* GetGlossMap();

    private:
        static API::Texture2D* s_preintegratedFG;
    };

    class PBRMaterialInstance : public MaterialInstance
    {
    public:
        PBRMaterialInstance(PBRMaterial* material);

        void SetEnviromentMap(API::TextureCube* texture);

        // PBR Statics
        void SetAlbedo(const QVector4D& color);
        void SetSpecular(const QVector3D& color);
        void SetGloss(float value);
        void UsingNormalMap(bool value);

        // PBR Maps
        void SetAlbedoMap(API::Texture2D* texture);
        void SetSpecularMap(API::Texture2D* texture);
        void SetNormalMap(API::Texture2D* texture);
        void SetGlossMap(API::Texture2D* texture); // TODO: Grayscale texture
    };
}
#endif