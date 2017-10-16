#ifndef CGFF_GL_TEXTURE_DEPTH_H
#define CGFF_GL_TEXTURE_DEPTH_H

#include "graphic/api/textureDepth.h"

namespace CGFF {

	class GLTextureDepth : public TextureDepth
	{
	public:
		GLTextureDepth(int width, int height);
		virtual ~GLTextureDepth() {};

		void bind(uint slot = 0) override;
		void unBind(uint slot = 0) override;

		inline GLuint getID() const { return m_glTexture.textureId(); }
		inline QString getName() const override { return m_name; }
		inline QString getFilepath() const override { return m_fileName; }
		inline int getWidth() const override { return m_width; }
		inline int getHeight() const override { return m_height; }

	private:
		void init();

	private:
		QString m_name;
		QString m_fileName;
		int m_width;
		int m_height;
		QOpenGLTexture m_glTexture;
        //GLuint m_handle;
	};

}

#endif
