#ifndef CGFF_PBR_MATERIAL_H
#define CGFF_PBR_MATERIAL_H

#include"material.h"

namespace CGFF {

    class PBRMaterial : public Material
    {
    public:
        PBRMaterial(QSharedPointer<ShaderProgram> shader);
        ~PBRMaterial();

        void setEnviromentMap(QSharedPointer<TextureCube> texture);

        // PBR Statics
        void setAlbedo(const QVector4D& color);
        void setSpecular(const QVector3D& color);
        void setGloss(float value);
        void usingNormalMap(bool value);

        // PBR Maps
        void setAlbedoMap(QSharedPointer<Texture2D> texture);
        void setSpecularMap(QSharedPointer<Texture2D> texture);
        void setNormalMap(QSharedPointer<Texture2D> texture);
        void setGlossMap(QSharedPointer<Texture2D> texture); // TODO: Grayscale texture

        QSharedPointer<QOpenGLTexture> getAlbedoMap();
        QSharedPointer<QOpenGLTexture> getSpecularMap();
        QSharedPointer<QOpenGLTexture> getNormalMap();
        QSharedPointer<QOpenGLTexture> getGlossMap();

    private:
        static QSharedPointer<Texture2D> s_preintegratedFG;
    };

    class PBRMaterialInstance : public MaterialInstance
    {
    public:
        PBRMaterialInstance(PBRMaterial* material);

        void setEnviromentMap(QSharedPointer<TextureCube> texture);

        // PBR Statics
        void setAlbedo(const QVector4D& color);
        void setSpecular(const QVector3D& color);
        void setGloss(float value);
        void usingNormalMap(bool value);

        // PBR Maps
        void setAlbedoMap(QSharedPointer<Texture2D> texture);
        void setSpecularMap(QSharedPointer<Texture2D> texture);
        void setNormalMap(QSharedPointer<Texture2D> texture);
        void setGlossMap(QSharedPointer<Texture2D> texture); // TODO: Grayscale texture
    };
}
#endif