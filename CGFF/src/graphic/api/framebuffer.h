#ifndef CGFF_FRAMEBUFFER_H
#define CGFF_FRAMEBUFFER_H

#include "maths/qtmaths.h"
#include "texture.h"

namespace CGFF {

	class Framebuffer
	{
	public:
		virtual void bind() = 0;
		virtual void unBind() = 0;
		virtual void clear() = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
		virtual QSharedPointer<Texture> getTexture() const = 0;
	protected:
		virtual void Init() {};
	};


}

#endif
