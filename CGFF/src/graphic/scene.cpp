#include "scene.h"

namespace CGFF {

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::add(QSharedPointer<Mesh>& mesh)
    {
        m_meshes.append(mesh);
    }

    void Scene::render(QSharedPointer<Renderer3D>& renderer)
    {
        for (QSharedPointer<Mesh> mesh : m_meshes)
            renderer->submit(mesh);
    }

}