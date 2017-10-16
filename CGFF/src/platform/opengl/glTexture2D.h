#ifndef CGFF_GL_TEXTURE_2D_H
#define CGFF_GL_TEXTURE_2D_H

#include "graphic/api/texture2D.h"
#include <QColor>

namespace CGFF {

	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(int width, int height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(int width, int height, int color, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(const QString& name, const QString& filename, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(const QString& name, const QImage& image, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
        GLTexture2D(int width, int height, const void* data, TextureParameters parameters = TextureParameters());

		virtual ~GLTexture2D();

		void setTexture(GLuint id);

		void bind(uint slot = 0) override;
		void unBind(uint slot = 0) override;

		inline GLuint getID() const override { return m_glTexture.textureId(); }
		inline QString getName() const override { return m_name; }
		inline QString getFilepath() const override { return m_fileName; }
		inline int getWidth() const override { return m_glTexture.width(); }
		inline int getHeight() const override { return m_glTexture.height(); }

	private:
		void load();
		void load(QColor color);
        void load(QImage image);
        void load(const void* data);

	private:
		QString m_name;
		QString m_fileName;
		int m_width;
		int m_height;
		TextureParameters m_parameters;
		TextureLoadOptions m_loadOptions;
		QOpenGLTexture m_glTexture;
	};
}

#endif