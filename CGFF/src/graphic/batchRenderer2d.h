#ifndef BATCH_RENDERER_2D_H
#define BATCH_RENDERER_2D_H

#include "../utils/types.h"
#include "../maths/qtmaths.h"
#include "renderer2d.h"
#include "renderable2d.h"
#include "meshFactory.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFramebufferObject>
#include <QPainter>
#include <cstddef>

namespace CGFF {
	
	class BatchRenderer2D : public Renderer2D
	{
	public:
		BatchRenderer2D(const QSize& screenSize);
		~BatchRenderer2D();

		void begin() override;
		void submit(QSharedPointer<Renderable2D>& renderable) override;
	    void drawString(const std::string& text, const QVector3D& position, QVector4D& color) override;
		void flush() override;
		void end() override;

        inline void setScreenSize(const QSize& size) { m_screenSize = size; }
        inline const QSize& getScreenSize() const { return m_screenSize; }
        inline void setViewportSize(const QSize& size) { m_viewportSize = size; }
        inline const QSize& getViewportSize() const { return m_viewportSize; }

	private:
		void init();
        float submitTexture(uint textureID);
        float submitTexture(const QSharedPointer<QOpenGLTexture>& texture);
       
	private:

		QOpenGLVertexArrayObject m_vao;
		QOpenGLBuffer* m_vboBuffer;
		QOpenGLBuffer* m_iboBuffer;
		VertexData* m_buffer;
        QSharedPointer<QOpenGLFramebufferObject> m_frameBuffer;
        QSharedPointer<QOpenGLShaderProgram> m_framebufferShader;
        QSharedPointer<QOpenGLFramebufferObject> m_postEffectsBuffer;
		GLsizei m_indexCount;
		QVector<GLuint> m_textureSlots;
        QSize m_viewportSize;
        QSize m_screenSize;
        int m_screenBuffer;
        QOpenGLFramebufferObjectFormat m_format;
        QSharedPointer<QOpenGLTexture> m_strTexture;

        MeshFactory::Quad m_screenQuad;
	};
}
#endif