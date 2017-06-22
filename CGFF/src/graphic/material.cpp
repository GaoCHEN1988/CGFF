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

    MaterialInstance::MaterialInstance(QSharedPointer<Material>& material)
        : m_material(material)
    {

    }
}