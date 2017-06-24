#include "material.h"

namespace CGFF {

    Material::Material(QSharedPointer<QOpenGLShaderProgram>& shader)
        : m_shader(shader)
    {
        //InitUniformStorage();
    }

    Material::~Material()
    {
    }

    void Material::bind() const
    {
        m_shader->bind();

        foreach(int key, m_uniformDatas.keys())
        {
            const UniformData& uniform = m_uniformDatas[key];
            switch (uniform.type)
            {
            case UniformType::QMatrix4x4:
            {
                m_shader->setUniformValue(key, *(QMatrix4x4 *)&uniform.data_pointer.data()[0]);
                break;
            }
            default:
                qDebug("Unknown uniform type!");
            }
        }
    }
    void Material::unbind() const
    {
        m_shader->release();
    }

    QSharedPointer<QOpenGLShaderProgram>  Material::getShader()
    {
        return m_shader;
    }


    MaterialInstance::MaterialInstance(QSharedPointer<Material>& material)
        : m_material(material)
    {
    }

    void MaterialInstance::bind() const
    {
        m_material->bind();
        foreach(int key, m_uniformDatas.keys())
        {
            const UniformData& uniform = m_uniformDatas[key];
            switch (uniform.type)
            {
            case UniformType::QMatrix4x4:
            {    
                m_material->getShader()->setUniformValue(key, *(QMatrix4x4 *)&uniform.data_pointer.data()[0]);
                break;
            }         
            default:
                qDebug("Unknown uniform type!");
            }
        }

    }
    void MaterialInstance::unbind() const
    {
        m_material->unbind();
    }

   
}