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
    }
    void Material::unbind() const
    {
        m_shader->release();
    }

    void Material::dumpUniformData() const
    {
    }

    QSharedPointer<QOpenGLShaderProgram>  Material::getShader() const
    {
        return m_shader;
    }


    MaterialInstance::MaterialInstance(QSharedPointer<Material>& material)
        : m_material(material)
    {

    }
}