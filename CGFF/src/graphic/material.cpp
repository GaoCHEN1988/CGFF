#include "material.h"

namespace CGFF {

    Material::Material(QSharedPointer<QOpenGLShaderProgram>& shader)
        : m_shader(shader)
    {
    }

    Material::~Material()
    {
    }

    void Material::bind() const
    {
        m_shader->bind();

        foreach(int key, m_uniformDatas.keys())
        {
            ResolveAndSetUniform(key, m_uniformDatas[key], m_shader);
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
        , m_isRendererData(true)
    {
    }

    void MaterialInstance::bind() const
    {
        m_material->bind();
        if (m_isRendererData)
        {
            foreach(int key, m_rUniformDatas.keys())
            {
                ResolveAndSetUniform(key, m_rUniformDatas[key], m_material->getShader());
            }
        }
        else
        {
            foreach(int key, m_uniformDatas.keys())
            {
                if (m_unsetUniformMap[key])
                    continue;

                ResolveAndSetUniform(key, m_uniformDatas[key], m_material->getShader());
            }
        }
    }
    void MaterialInstance::unbind() const
    {
        m_material->unbind();
    }


    void MaterialInstance::unsetUniform(const QString& name, bool unset)
    {
        int key = m_material->getShader()->uniformLocation(name);
        m_unsetUniformMap[key] = unset;
        m_isRendererData = false;
    }
   
    void MaterialInstance::setRendererUniform(const RendererUniform& uniform)
    {
        int index = m_material->getShader()->uniformLocation(uniform.uniform);
        if (-1 == index)
        {
            qFatal("Could not find uniform %s", uniform.uniform);
        }

        m_rUniformDatas[index] = uniform;

        m_isRendererData = true;
    }
}