#ifndef MATERIAL_H
#define MATERIAL_H

#include "../utils/qtopengl.h"
#include <QOpenGLShaderProgram>

namespace CGFF {

    class Material
    {
    public:
        Material(QSharedPointer<QOpenGLShaderProgram>& shader);
        ~Material();

        void bind() const;
        void unbind() const;
        void dumpUniformData() const;

    private:
        QSharedPointer<QOpenGLShaderProgram> m_shader;
    };

    class MaterialInstance
    {
    public:
        MaterialInstance(QSharedPointer<Material>& material);

        inline QSharedPointer<Material>& getMaterial() { return m_material; }

    private:
        QSharedPointer<Material> m_material;
    };
}

#endif
