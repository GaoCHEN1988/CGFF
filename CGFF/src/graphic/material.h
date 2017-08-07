#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils/qtopengl.h"
#include "utils/types.h"
#include "shader/shaderProgram.h"
#include "api/texture2D.h"

//#include <QByteArray>
//#include <QDataStream>


namespace CGFF {

#define IMPLEMENT_MATERIAL_SET_UNIFORM(Type)  template<>\
    inline void Material::setUniform<Type>(const char * name, const Type& value)\
    {\
        int index = m_shader->uniformLocation(name);\
        if (-1 == index)\
        {\
            qFatal("Could not find uniform %s", name);\
        }\
        UniformData uniform_data;\
        uniform_data.type = UniformType::Type;\
        uniform_data.data_pointer = QSharedPointer<char>(new char[sizeof(Type)]);\
        memcpy(uniform_data.data_pointer.data(), &value, sizeof(Type));\
        m_uniformDatas[index] = uniform_data;\
    }\

#define IMPLEMENT_MATERIALINSTANCE_SET_UNIFORM(Type)  template<>\
    inline void MaterialInstance::setUniform<Type>(const char * name, const Type& value)\
    {\
        int index = m_material->getShader()->uniformLocation(name);\
        if (-1 == index)\
        {\
            qFatal("Could not find uniform %s", name);\
        }\
        UniformData uniform_data;\
        uniform_data.type = UniformType::Type;\
        uniform_data.data_pointer = QSharedPointer<char>(new char[sizeof(Type)]);\
        memcpy(uniform_data.data_pointer.data(), &value, sizeof(Type));\
        m_uniformDatas[index] = uniform_data;\
    }\

#define IMPLEMENT_SET_UNIFORM(type) IMPLEMENT_MATERIAL_SET_UNIFORM(type)\
    IMPLEMENT_MATERIALINSTANCE_SET_UNIFORM(type)

    class Material
    {
    public:
        Material(QSharedPointer<QOpenGLShaderProgram>& shader);
        virtual ~Material();

        void bind() const;
        void unbind() const;

        QSharedPointer<QOpenGLShaderProgram> getShader();

        template<typename T>
        void setUniform(const char *name, const T& value)
        {
            qFatal("Unknown uniform type!");
        }

    private:
        QSharedPointer<QOpenGLShaderProgram> m_shader;
        QHash<int, UniformData> m_uniformDatas;
    };

    class MaterialInstance
    {
    public:

        MaterialInstance(QSharedPointer<Material>& material);
        void bind() const;
        void unbind() const;

        inline QSharedPointer<Material>& getMaterial() { return m_material; }

        template<typename T>
        void setUniform(const char * name, const T& value)
        {
            qFatal("Unknown uniform type!");
        }
        void setRendererUniform(const RendererUniform& uniform);
        void unsetUniform(const QString& name, bool unset);

    private:
        QSharedPointer<Material> m_material;
        QHash<int, UniformData> m_uniformDatas;
        QHash<int, RendererUniform> m_rUniformDatas;
        QHash<int, bool> m_unsetUniformMap;
        bool m_isRendererData;
    };

    IMPLEMENT_SET_UNIFORM(GLfloat)
    IMPLEMENT_SET_UNIFORM(GLint)
    IMPLEMENT_SET_UNIFORM(GLuint)
    IMPLEMENT_SET_UNIFORM(QVector2D)
    IMPLEMENT_SET_UNIFORM(QVector3D)
    IMPLEMENT_SET_UNIFORM(QVector4D)
    IMPLEMENT_SET_UNIFORM(QMatrix2x2)
    IMPLEMENT_SET_UNIFORM(QMatrix2x3)
    IMPLEMENT_SET_UNIFORM(QMatrix2x4)
    IMPLEMENT_SET_UNIFORM(QMatrix3x2)
    IMPLEMENT_SET_UNIFORM(QMatrix3x3)
    IMPLEMENT_SET_UNIFORM(QMatrix3x4)
    IMPLEMENT_SET_UNIFORM(QMatrix4x2)
    IMPLEMENT_SET_UNIFORM(QMatrix4x3)
    IMPLEMENT_SET_UNIFORM(QMatrix4x4)
}

#endif
