#ifndef CGFF_FRAMEBUFFER_DEPTH_H
#define CGFF_FRAMEBUFFER_DEPTH_H

#include "framebuffer.h"

namespace CGFF {

	class FramebufferDepth : public Framebuffer
	{
	public:
		static QSharedPointer<FramebufferDepth> create(int width, int height);
	};
}

#endif