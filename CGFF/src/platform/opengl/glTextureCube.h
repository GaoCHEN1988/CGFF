#ifndef CGFF_GL_TEXTURE_CUBE_H
#define CGFF_GL_TEXTURE_CUBE_H

#include "graphic/api/textureCube.h"

namespace CGFF {

	class GLTextureCube : public TextureCube
	{
	public:
		GLTextureCube(const QString& name, const QString& filepath);
		GLTextureCube(const QString& name, const QStringList& files);
		GLTextureCube(const QString& name, const QStringList& files, int mips, InputFormat format);
		virtual ~GLTextureCube();

		void bind(uint slot = 0) override;
		void unBind(uint slot = 0) override;

		inline GLuint getID() const { return m_glTexture.textureId(); }
		inline QString getName() const override { return m_name; }
		inline QString getFilepath() const override { return m_fileNames[0]; }
		inline QStringList getFilepathList() const { return m_fileNames; }
		inline int getWidth() const override { return m_glTexture.width(); }
		inline int getHeight() const override { return m_glTexture.height(); }

	private:
		void loadFromFiles();
		void loadFromVCross(int mips);
		void resolvePhysicalPath(const QStringList& files);
	private:
		QString m_name;
		QStringList m_fileNames;
		int m_width;
		int m_height;
		InputFormat m_inputFormat;
		TextureParameters m_parameters;
		TextureLoadOptions m_loadOptions;
		QOpenGLTexture m_glTexture;
	};

}
#endif