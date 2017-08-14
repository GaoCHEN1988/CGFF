#include "layoutBuffer.h"

namespace CGFF {

	LayoutBuffer::LayoutBuffer()
		: m_size(0)
	{

	}

	void LayoutBuffer::pushLayout(const QString& name, uint type, uint size, uint count, bool normalized)
	{
        m_layout.append({ name, type, size, count, m_size, normalized });

        m_size += size * count;
	}

}