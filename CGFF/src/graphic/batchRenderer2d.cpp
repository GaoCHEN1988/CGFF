#include "batchRenderer2d.h"


namespace CGFF {

	BatchRenderer2D::BatchRenderer2D() 
		: Renderer2D()
		, m_indexCount(0)
	{
		initializeOpenGLFunctions();
		
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		m_vao.destroy();
		m_vboBuffer->destroy();
		m_iboBuffer->destroy();

		delete m_vboBuffer;
		delete m_iboBuffer;
	}

	void BatchRenderer2D::init()
	{
		m_vao.create();
		m_vao.bind();
		
		m_vboBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
		m_vboBuffer->create();
		m_vboBuffer->bind();
		m_vboBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
		m_vboBuffer->allocate(NULL, RENDERER_BUFFER_SIZE);
		
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)(offsetof(VertexData, VertexData::tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)(offsetof(VertexData, VertexData::color)));
		
		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

		int offset = 0;

		for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_iboBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
		m_iboBuffer->create();
		m_iboBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
		m_iboBuffer->bind();
		m_iboBuffer->allocate(indices, RENDERER_INDICES_SIZE* sizeof(GLuint));

		m_indexCount = 0;
	}

	void BatchRenderer2D::begin()
	{
		int test = sizeof(*m_vboBuffer);
		m_vboBuffer->bind();
		m_buffer = (VertexData*)m_vboBuffer->map(QOpenGLBuffer::WriteOnly);
	}
	void BatchRenderer2D::submit(QSharedPointer<Renderable2D> renderable)
	{
		const QVector3D& position = renderable->getPosition();
		const QVector2D& size = renderable->getSize();
		const QVector4D& color = renderable->getColor();
		const std::vector<QVector2D>& UV = renderable->getUV();
		const GLuint textureId = renderable->getTextureID();

		float ts = 0.0;

		if (textureId > 0)
		{
			bool found = false;
			for (int i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == textureId)
				{
					found = true;
					ts = static_cast<float>(i+1);
					break;
				}
			}

			if (!found)
			{
				if (m_textureSlots.size() >= 32)
				{
					end();
					flush();
					begin();
				}
				m_textureSlots.push_back(textureId);
				ts = static_cast<float>(m_textureSlots.size());
			}
		}

		m_buffer->vertex = *m_tranformationBack * position;
		m_buffer->uv = UV[0];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_tranformationBack * QVector3D(position.x(), position.y() + size.y(), position.z());
		m_buffer->uv = UV[1];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_tranformationBack * QVector3D(position.x() + size.x(), position.y() + size.y(), position.z());
		m_buffer->uv = UV[2];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_tranformationBack * QVector3D(position.x() + size.x(), position.y(), position.z());
		m_buffer->uv = UV[3];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_indexCount += 6;
	}

	void BatchRenderer2D::flush() 
	{
		for (int i = 0; i < m_textureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
		}
		m_vao.bind();
		m_iboBuffer->bind();
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

		m_iboBuffer->release();
		m_vao.release();
		m_vboBuffer->release();
		m_indexCount = 0;
	}
	void BatchRenderer2D::end()
	{
		m_vboBuffer->unmap();
	}
}