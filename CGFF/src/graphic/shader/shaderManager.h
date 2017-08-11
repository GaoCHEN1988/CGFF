#ifndef CGFF_SHADER_MANAGER_H
#define CGFF_SHADER_MANAGER_H

#include "utils/qtopengl.h"
#include "shader.h"

namespace CGFF {

    class ShaderManager
    {
    private:
        ShaderManager() {}
    public:
        static void add(QSharedPointer<Shader> shader);
        static QSharedPointer<Shader> get(const QString& name);
        static void clean();
        static void reload(const QString& name);

    private:
        static QVector<QSharedPointer<Shader>> s_shaders;
    };
}

#endif