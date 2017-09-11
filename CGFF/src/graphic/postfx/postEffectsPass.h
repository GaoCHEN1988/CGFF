#ifndef POST_EFFECTS_PASS_H
#define POST_EFFECTS_PASS_H

#include "utils/qtopengl.h"
#include "graphic/api/framebuffer.h"
#include "graphic/material.h"
#include "graphic/mesh.h"

namespace CGFF {
    class PostEffectsPass
    {

    public:
        PostEffectsPass(const QSharedPointer<Shader>& shader, QSize& size);
        virtual ~PostEffectsPass();
        void bind();
        void unBind();
        void setSize(QSize size);

        void renderPass(const QSharedPointer<Framebuffer>& target, const QSharedPointer<Mesh>& mesh);

    private:
        QSharedPointer<Material> m_material;
        QSize m_size;
    };
}

#endif
