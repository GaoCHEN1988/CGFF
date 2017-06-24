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
            case UniformType::GLfloat:
            {
                m_shader->setUniformValue(key, *(GLfloat *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::GLint:
            {
                m_shader->setUniformValue(key, *(GLint *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::GLuint:
            {
                m_shader->setUniformValue(key, *(GLuint *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QVector2D:
            {
                m_shader->setUniformValue(key, *(QVector2D *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QVector3D:
            {
                m_shader->setUniformValue(key, *(QVector3D *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QVector4D:
            {
                m_shader->setUniformValue(key, *(QVector4D *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix2x2:
            {
                m_shader->setUniformValue(key, *(QMatrix2x2 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix2x3:
            {
                m_shader->setUniformValue(key, *(QMatrix2x3 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix2x4:
            {
                m_shader->setUniformValue(key, *(QMatrix2x4 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix3x2:
            {
                m_shader->setUniformValue(key, *(QMatrix3x2 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix3x3:
            {
                m_shader->setUniformValue(key, *(QMatrix3x3 *)&uniform.data_pointer.data()[0]);
                break;
            }    
            case UniformType::QMatrix3x4:
            {
                m_shader->setUniformValue(key, *(QMatrix3x4 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix4x2:
            {
                m_shader->setUniformValue(key, *(QMatrix4x2 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix4x3:
            {
                m_shader->setUniformValue(key, *(QMatrix4x3 *)&uniform.data_pointer.data()[0]);
                break;
            }
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
            if (m_unsetUniformMap[key])
                continue;

            const UniformData& uniform = m_uniformDatas[key];
            switch (uniform.type)
            {
            case UniformType::GLfloat:
            {
                m_material->getShader()->setUniformValue(key, *(GLfloat *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::GLint:
            {
                m_material->getShader()->setUniformValue(key, *(GLint *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::GLuint:
            {
                m_material->getShader()->setUniformValue(key, *(GLuint *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QVector2D:
            {
                m_material->getShader()->setUniformValue(key, *(QVector2D *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QVector3D:
            {
                m_material->getShader()->setUniformValue(key, *(QVector3D *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QVector4D:
            {
                m_material->getShader()->setUniformValue(key, *(QVector4D *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix2x2:
            {
                m_material->getShader()->setUniformValue(key, *(QMatrix2x2 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix2x3:
            {
                m_material->getShader()->setUniformValue(key, *(QMatrix2x3 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix2x4:
            {
                m_material->getShader()->setUniformValue(key, *(QMatrix2x4 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix3x2:
            {
                m_material->getShader()->setUniformValue(key, *(QMatrix3x2 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix3x3:
            {
                m_material->getShader()->setUniformValue(key, *(QMatrix3x3 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix3x4:
            {
                m_material->getShader()->setUniformValue(key, *(QMatrix3x4 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix4x2:
            {
                m_material->getShader()->setUniformValue(key, *(QMatrix4x2 *)&uniform.data_pointer.data()[0]);
                break;
            }
            case UniformType::QMatrix4x3:
            {
                m_material->getShader()->setUniformValue(key, *(QMatrix4x3 *)&uniform.data_pointer.data()[0]);
                break;
            }
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


    void MaterialInstance::unsetUniform(const QString& name, bool unset)
    {
        int key = m_material->getShader()->uniformLocation(name);
        m_unsetUniformMap[key] = unset;
    }
   
}