#ifndef GL_TEXTURE_CUBE_H
#define GL_TEXTURE_CUBE_H

#include "graphic/api/textureCube.h"

namespace CGFF {

	class GLTextureCube : public TextureCube
	{
	public:
		GLTextureCube(const QString& name, const QString& filepath);
		GLTextureCube(const QString& name, const QStringList& files);
		GLTextureCube(const QString& name, const QStringList& files, int mips, InputFormat format);
		virtual ~GLTextureCube() {};

		inline QString getName() const { return m_name; }
		inline QStringList getFilepath() const { return m_fileNames; }

	private:
		void loadFromFiles();

	private:
		QString m_name;
		QStringList m_fileNames;
		int m_width;
		int m_height;
		InputFormat m_inputFormat;
		TextureParameters m_parameters;
		TextureLoadOptions m_loadOptions;
	};

}
#endif