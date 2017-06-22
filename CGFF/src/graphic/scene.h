#ifndef SCENE_H
#define SCENE_H

#include "mesh.h"
#include "renderer3d.h"

namespace CGFF {

    class Scene
    {
    private:
        QVector<QSharedPointer<Mesh>> m_meshes; // TODO: Replace with component-based Entities!
    public:
        Scene();
        ~Scene();
        void add(QSharedPointer<Mesh>& mesh);
        void render(QSharedPointer<Renderer3D>& renderer);

        const QVector<QSharedPointer<Mesh>>& getMeshes() const { return m_meshes; }
    };
}
#endif
