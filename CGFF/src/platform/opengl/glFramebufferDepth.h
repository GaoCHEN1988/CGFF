#ifndef CGFF_GL_FRAMEBUFFER_DEPTH_H
#define CGFF_GL_FRAMEBUFFER_DEPTH_H

#include "utils/qtopengl.h"
#include "graphic/api/framebufferDepth.h"
#include "glTextureDepth.h"

namespace CGFF {

	class GLFramebufferDepth : public FramebufferDepth
	{
	public:
		GLFramebufferDepth(int width, int height);
		~GLFramebufferDepth();

		void bind() override;
		void unBind() override;
		void clear() override;

		int getWidth() const override;
		int getHeight() const override;
        QSize getSize() const override;

		QSharedPointer<Texture> getTexture() const override;
	private:
		void init();

	private:
		GLuint m_framebufferID;

		GLuint m_width, m_height;
		QSharedPointer<GLTextureDepth> m_glTexture;
	};
}

#endif
