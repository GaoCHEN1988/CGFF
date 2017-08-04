#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "utils/qtopengl.h"
#include "shaderProgram.h"

namespace CGFF {

    class ShaderManager
    {
    private:
        ShaderManager() {}
    public:
        static void add(QSharedPointer<ShaderProgram> shader);
        static QSharedPointer<ShaderProgram> get(const QString& name);
        static void clean();
        static void reload(const QString& name);

    private:
        static QVector<QSharedPointer<ShaderProgram>> s_shaders;
    };
}

#endif