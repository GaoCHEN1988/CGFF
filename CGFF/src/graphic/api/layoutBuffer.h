#ifndef CGFF_LAYOUT_BUFFER_H
#define CGFF_LAYOUT_BUFFER_H

#include "utils/types.h"
#include "context.h"

namespace CGFF {

	struct BufferElement
	{
		QString name;
		uint type;
		uint size;
		uint count;
		uint offset;
		bool normalized;
	};

	class LayoutBuffer
	{
	public:
		LayoutBuffer();

		template<typename T>
		void push(const QString& name, uint count = 1, bool normalized = false)
		{
			qFatal("Unkown layout type!");
		}

		template<>
		void push<uint>(const QString& name, uint count, bool normalized)
		{
			switch (Context::getRenderAPI())
			{
			case RenderAPI::OPENGL:
				pushLayout(name, GL_UNSIGNED_INT, sizeof(uint), count, normalized);
				break;
			case RenderAPI::DIRECT3D:
				qFatal("DiectX not supported!");
				break;
			}
		}

		template<>
		void push<byte>(const QString& name, uint count, bool normalized)
		{
			switch (Context::getRenderAPI())
			{
			case RenderAPI::OPENGL:
				pushLayout(name, GL_UNSIGNED_BYTE, sizeof(byte), count, normalized);
				break;
			case RenderAPI::DIRECT3D:
				qFatal("DiectX not supported!");
				break;
			}
		}

		template<>
		void push<QVector2D>(const QString& name, uint count, bool normalized)
		{
			switch (Context::getRenderAPI())
			{
			case RenderAPI::OPENGL:
				pushLayout(name, GL_FLOAT, sizeof(float), 2, normalized);
				break;
			case RenderAPI::DIRECT3D:
				qFatal("DiectX not supported!");
				break;
			}
		}

		template<>
		void push<QVector3D>(const QString& name, uint count, bool normalized)
		{
			switch (Context::getRenderAPI())
			{
			case RenderAPI::OPENGL:
				pushLayout(name, GL_FLOAT, sizeof(float), 3, normalized);
				break;
			case RenderAPI::DIRECT3D:
				qFatal("DiectX not supported!");
				break;
			}
		}

		template<>
		void push<QVector4D>(const QString& name, uint count, bool normalized)
		{
			switch (Context::getRenderAPI())
			{
			case RenderAPI::OPENGL:
				pushLayout(name, GL_FLOAT, sizeof(float), 4, normalized);
				break;
			case RenderAPI::DIRECT3D:
				qFatal("DiectX not supported!");
				break;
			}
		}

		inline const QVector<BufferElement>& getLayout() const { return m_layout; }
		inline uint getStride() const { return m_size; }

	private:
		void pushLayout(const QString& name, uint type, uint size, uint count, bool normalized);

	private:
		uint m_size;
		QVector<BufferElement> m_layout;
	};
}

#endif
