#ifndef LAYER_H
#define LAYER_H

#include "../renderer2d.h"
#include "../renderable2d.h"
#include "../batchRenderer2d.h"
#include "../maths/qtmaths.h"
#include <QOpenGLShaderProgram>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

namespace CGFF {
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();
		virtual void add(QSharedPointer<Renderable2D> renderable);
		virtual void render();

	protected:
		Layer(QSharedPointer<QOpenGLShaderProgram> shader,/* QSharedPointer<Renderer2D> renderer, */QMatrix4x4 projectionMatrix);

	protected:
		QSharedPointer<QOpenGLShaderProgram> m_shader;
		QSharedPointer<BatchRenderer2D> m_renderer;
		std::vector<QSharedPointer<Renderable2D>> m_renderables;
		QMatrix4x4 m_projectionMatrix;
	};
}

#endif