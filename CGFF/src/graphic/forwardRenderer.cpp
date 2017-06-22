#include "forwardRenderer.h"

namespace CGFF {
    ForwardRenderer::ForwardRenderer()
    {}
    void ForwardRenderer::init()
    {
    }
    void ForwardRenderer::begin() 
    {
        m_drawQueue.clear();
    }

    void ForwardRenderer::submit(QSharedPointer<Mesh>& mesh) 
    {
        m_drawQueue.push_back(mesh);
    }
    void ForwardRenderer::end() 
    {
    }
    void ForwardRenderer::flush() 
    {
        for (uint i = 0; i < m_drawQueue.size(); i++)
            m_drawQueue[i]->render(*this);
    }
}