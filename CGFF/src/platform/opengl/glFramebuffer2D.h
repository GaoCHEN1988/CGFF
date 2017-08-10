#ifndef GL_FRAMEBUFFER_2D_H
#define GL_FRAMEBUFFER_2D_H

#include "utils/qtopengl.h"
#include "graphic/api/framebuffer2D.h"
#include "glTexture2D.h"

namespace CGFF {

	class GLFramebuffer2D : public Framebuffer2D
	{

	public:
		GLFramebuffer2D(int width, int height);
		~GLFramebuffer2D();

		void bind() override;
		void unBind() override;
		void clear() override;

		int getWidth() const override;
		int getHeight() const override;

		QSharedPointer<Texture> getTexture() const override;

		void setClearColor(const QVector4D& color) override;

	private:
		void init();

	private:
		GLuint m_framebufferHandle;
		GLuint m_depthbufferHandle;

		QSharedPointer<GLTexture2D> m_glTexture;

		int m_width, m_height;
		QVector4D m_clearColor;
	};
}

#endif
