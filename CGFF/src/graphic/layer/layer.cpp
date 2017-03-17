#include "layer.h"

namespace CGFF {

	Layer::Layer() 
	{
		
	}

	Layer::~Layer() 
	{
		m_renderables.clear();
	}
	Layer::Layer(QSharedPointer<QOpenGLShaderProgram> shader, QSharedPointer<Renderer2D> renderer, QMatrix4x4 projectionMatrix)
		:m_shader(shader)
		, m_renderer(renderer)
		, m_projectionMatrix(projectionMatrix)
	{
		m_shader->bind();
		m_shader->setUniformValue("projMatrix", m_projectionMatrix);
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
		for (QSharedPointer<Renderable2D> r : m_renderables)
		{
			m_renderer->submit(r);
		}
		m_renderer->end();

		m_renderer->flush();
	}

}