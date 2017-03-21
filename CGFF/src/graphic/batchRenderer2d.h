#ifndef BATCH_RENDERER_2D_H
#define BATCH_RENDERER_2D_H

#include "renderer2d.h"
#include "../maths/qtmaths.h"
#include "renderable2d.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <cstddef>

namespace CGFF {

#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITES_SIZE RENDERER_VERTEX_SIZE*4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITES_SIZE*RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES*6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_COLOR_INDEX 2
	
	class BatchRenderer2D : public Renderer2D, protected QOpenGLFunctions_4_4_Core
	{
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void begin() override;
		void submit(QSharedPointer<Renderable2D> renderable) override;
		void flush() override;
		void end() override;

	private:
		void init();

	private:

		QOpenGLVertexArrayObject m_vao;
		QOpenGLBuffer* m_vboBuffer;
		QOpenGLBuffer* m_iboBuffer;
		VertexData* m_buffer;
		GLsizei m_indexCount;
	};
}
#endif