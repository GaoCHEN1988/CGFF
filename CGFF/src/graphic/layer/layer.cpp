#include "layer.h"

namespace CGFF {

	Layer::~Layer() 
	{
	}
	Layer::Layer(QSharedPointer<Renderer2D> renderer, QSharedPointer<QOpenGLShaderProgram>  shader, /*QSharedPointer<Renderer2D> renderer,*/ QMatrix4x4 projectionMatrix)
		: m_renderer(renderer)
        , m_shader(shader)
		, m_projectionMatrix(projectionMatrix)
	{
		//m_renderer = QSharedPointer<BatchRenderer2D>(new BatchRenderer2D());
		m_shader->bind();
		m_shader->setUniformValue("projMatrix", m_projectionMatrix);
		GLint texIDs[] =
		{
			0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
			11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
			22, 23, 24, 25, 26, 27, 28, 29, 30, 31
		};
		m_shader->setUniformValueArray("textures", texIDs, 32);

		m_shader->release();
	}

	void Layer::add(QSharedPointer<Renderable2D> renderable)
	{
		m_renderables.push_back(renderable);
	}

	void Layer::render()
	{
		m_shader->bind();	
		m_renderer->begin();
		for (const QSharedPointer<Renderable2D> r : m_renderables)
		{
			//m_renderer->submit(r);
			r->submit(m_renderer);
		}
		//m_renderer->drawString("test", QVector3D(6, 4, 0), QVector4D(1, 1, 1, 0));
		m_renderer->end();
		m_renderer->flush();
		m_shader->release();
	}

}