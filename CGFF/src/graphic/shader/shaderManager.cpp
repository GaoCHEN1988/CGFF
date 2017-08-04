#include "shaderManager.h"

namespace CGFF {

    QVector<QSharedPointer<ShaderProgram>> ShaderManager::s_shaders;

    void ShaderManager::add(QSharedPointer<ShaderProgram> shader)
    {
        s_shaders.append(shader);
    }

    QSharedPointer<ShaderProgram> ShaderManager::get(const QString& name)
    {
        for (QSharedPointer<ShaderProgram> shader : s_shaders)
        {
            if (shader->getName() == name)
                return shader;
        }
        return nullptr;
    }

    void ShaderManager::clean()
    {
        s_shaders.clear();
    }

    void ShaderManager::reload(const QString& name)
    {
        for (QSharedPointer<ShaderProgram> shader : s_shaders)
        {
            if (shader->getName() == name)
                shader->reload();
        }
    }

}