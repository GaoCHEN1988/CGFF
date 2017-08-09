#ifndef GL_FRAMEBUFFER_2D_H
#define GL_FRAMEBUFFER_2D_H

#include "graphic/api/framebuffer2D.h"

namespace CGFF {

	class GLFramebuffer2D : public Framebuffer2D
	{

	public:
		GLFramebuffer2D(int width, int height);
		~GLFramebuffer2D();

	private:
		void Init();

	private:
		int m_FramebufferHandle;
		int m_DepthbufferHandle;

		int m_Width, m_Height;
		maths::vec4 m_ClearColor;
		API::GLTexture2D* m_Texture;
	};
}

#endif
