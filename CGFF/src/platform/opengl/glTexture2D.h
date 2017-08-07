#ifndef GL_TEXTURE_2D_H
#define GL_TEXTURE_2D_H

#include "graphic/api/texture2D.h"

namespace CGFF {

	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(int width, int height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(int width, int height, int color, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(const QString& name, const QString& filename, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());

		virtual ~GLTexture2D() {};

	private: 
		void load();

	private:
		QString m_name;
		QString m_fileName;
		int m_width;
		int m_height;
		TextureParameters m_parameters;
		TextureLoadOptions m_loadOptions;
	};
}

#endif