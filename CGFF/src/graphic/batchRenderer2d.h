#ifndef BATCH_RENDERER_2D_H
#define BATCH_RENDERER_2D_H

#include "../utils/types.h"
#include "../maths/qtmaths.h"
#include "renderer2d.h"
#include "renderable2d.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFramebufferObject>
#include <cstddef>

namespace CGFF {

//#define RENDERER_MAX_SPRITES 60000
////#define RENDERER_VERTEX_SIZE sizeof(VertexData)
//#define RENDERER_SPRITES_SIZE RENDERER_VERTEX_SIZE*4
//#define RENDERER_BUFFER_SIZE RENDERER_SPRITES_SIZE*RENDERER_MAX_SPRITES
//#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES*6
//#define RENDERER_MAX_TEXTURES 32
//
//#define SHADER_VERTEX_INDEX     0
//#define SHADER_UV_INDEX         1
//#define SHADER_MASK_UV_INDEX	2
//#define SHADER_TID_INDEX        3
//#define SHADER_MID_INDEX        4
//#define SHADER_COLOR_INDEX      5

    enum class RenderTarget
    {
        SCREEN = 0,
        BUFFER = 1
    };
	
	class BatchRenderer2D : public Renderer2D, protected QOpenGLFunctions_4_4_Core
	{
	public:
		BatchRenderer2D(const QSize& screenSize);
		~BatchRenderer2D();

		void begin() override;
		void submit(QSharedPointer<Renderable2D> renderable) override;
	    void drawString(const std::string& text, const QVector3D& position, QVector4D& color) override;
		void flush() override;
		void end() override;

        inline void SetScreenSize(const QSize& size) { m_screenSize = size; }
        inline const QSize& GetScreenSize() const { return m_screenSize; }
        inline void SetViewportSize(const QSize& size) { m_viewportSize = size; }
        inline const QSize& GetViewportSize() const { return m_viewportSize; }

        inline void SetRenderTarget(RenderTarget target) { m_renderTarget = target; }
        inline const RenderTarget GetRenderTarget() const { return m_renderTarget; }
	private:
		void init();
        float submitTexture(uint textureID);
        float submitTexture(const QSharedPointer<QOpenGLTexture>& texture);

	private:

		QOpenGLVertexArrayObject m_vao;
		QOpenGLBuffer* m_vboBuffer;
		QOpenGLBuffer* m_iboBuffer;
		VertexData* m_buffer;
        QOpenGLFramebufferObject* m_frameBuffer;
        QSharedPointer<QOpenGLShaderProgram> m_framebufferShader;
		GLsizei m_indexCount;
		QVector<GLuint> m_textureSlots;
        QSize m_viewportSize;
        QSize m_screenSize;
        RenderTarget m_renderTarget;
        GLuint m_screenQuad;
        int m_screenBuffer;
	};
}
#endif