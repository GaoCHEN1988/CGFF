#include "shaderManager.h"

namespace CGFF {

    QVector<QSharedPointer<Shader>> ShaderManager::s_shaders;

    void ShaderManager::add(QSharedPointer<Shader> shader)
    {
        s_shaders.append(shader);
    }

    QSharedPointer<Shader> ShaderManager::get(const QString& name)
    {
        for (QSharedPointer<Shader> shader : s_shaders)
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
        for (QSharedPointer<Shader> shader : s_shaders)
        {
            if (shader->getName() == name)
                shader->reload();
        }
    }

	void ShaderManager::reload(const QSharedPointer<Shader>& shader)
	{
		for (QSharedPointer<Shader> s : s_shaders)
		{
			if (s == shader)
				s->reload();
		}
	}
}