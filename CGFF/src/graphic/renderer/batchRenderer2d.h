#ifndef CGFF_BATCH_RENDERER_2D_H
#define CGFF_BATCH_RENDERER_2D_H

#include "utils/types.h"
#include "maths/qtmaths.h"
#include "renderer2d.h"
#include "graphic/renderable2d.h"
#include "graphic/api/framebuffer2D.h"
#include "graphic/api/vertexArray.h"
#include "graphic/api/indexBuffer.h"
#include "graphic/mesh.h"
#include "graphic/material.h"

#include <cstddef>
#include <QPainter>
//#include <QOpenGLFramebufferObject>
#define FRAMEBUDDER_TEST

namespace CGFF {

	struct UniformBuffer
	{
		QSharedPointer<uchar> buffer_pointer;
		uint size;
		UniformBuffer()
		{
			buffer_pointer = nullptr;
			size = 0;
		};

		UniformBuffer(QSharedPointer<uchar> buffer, uint size)
			: buffer_pointer(buffer), size(size)
		{
			memset(buffer_pointer.data(), 0, size);
		}
	};

	struct BR2DSystemUniform
	{
		UniformBuffer buffer;
		uint offset;

		BR2DSystemUniform() {}
		BR2DSystemUniform(const UniformBuffer& buffer, uint offset)
			: buffer(buffer), offset(offset)
		{
		}
	};
	
	class BatchRenderer2D : public Renderer2D
	{
	public:
		BatchRenderer2D(const QSize& screenSize);
		~BatchRenderer2D();

		void begin() override;
		void submit(QSharedPointer<Renderable2D>& renderable) override;
        void drawString(QString text, const QVector3D& position, QVector4D& color, QFont font) override;
		void flush() override;
		void end() override;
		void close() override;

		void setCamera(QSharedPointer<Camera> camera) override;

        void drawLine(float x0, float y0, float x1, float y1, QVector4D color = QVector4D(1, 1, 1, 1), float thickness = 1.0f) override;
        void drawLine(const QVector2D& start, const QVector2D& end, QVector4D color = QVector4D(1, 1, 1, 1), float thickness = 1.0f) override;
        void drawRect(float x, float y, float width, float height, QVector4D color = QVector4D(1, 1, 1, 1), float thickness = 1.0f) override;
        void drawRect(const QRect& rectangle, QVector4D color = QVector4D(1, 1, 1, 1)) override;
        void fillRect(float x, float y, float width, float height, QVector4D color = QVector4D(1,1,1,1)) override;
        void fillRect(const QRect& rectangle, QVector4D color = QVector4D(1, 1, 1, 1)) override;

        inline void setScreenSize(const QSize& size) { m_screenSize = size; }
        inline const QSize& getScreenSize() const { return m_screenSize; }
        inline void setViewportSize(const QSize& size) { m_viewportSize = size; }
        inline const QSize& getViewportSize() const { return m_viewportSize; }
     
	private:
		void init();
        //float submitTexture(uint textureID);
        float submitTexture(const QSharedPointer<Texture>& texture);
       
	private:

		//QOpenGLVertexArrayObject m_vao;
		//QOpenGLBuffer* m_vboBuffer;
		//QOpenGLBuffer* m_iboBuffer;
		QSharedPointer<Shader> m_shader;
		QVector<BR2DSystemUniform> m_systemUniforms;
		QVector<UniformBuffer> m_systemUniformBuffers;

		QSharedPointer<VertexArray> m_vertexArray;
		QSharedPointer<IndexBuffer> m_indexBuffer;
		QSharedPointer<IndexBuffer> m_lineIBO;

		VertexData* m_buffer;
        QSharedPointer<Framebuffer2D> m_frameBuffer;
        //QSharedPointer<QOpenGLShaderProgram> m_framebufferShader;
        QSharedPointer<Framebuffer2D> m_postEffectsBuffer;
        QSharedPointer<Material> m_framebufferMaterial;
        QSharedPointer<Material> m_postEffectsMaterial;
        QSharedPointer<Material> m_screenMaterial;

		GLsizei m_indexCount;
		//QVector<GLuint> m_textureSlots;
        QSize m_viewportSize;
        QSize m_screenSize;
        //int m_screenBuffer;
        //QOpenGLFramebufferObjectFormat m_format;
        //QSharedPointer<QOpenGLTexture> m_strTexture;
		QVector<QSharedPointer<Texture>> m_strTextures;
		QVector<QSharedPointer<Texture>> m_textures;
		//QSharedPointer<VertexArray> m_ScreenQuad;
		QSharedPointer<Camera> m_camera;
        QSharedPointer<Mesh> m_screenQuad;
		uint* m_indices;
	};
}
#endif