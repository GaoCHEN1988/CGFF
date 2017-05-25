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
        glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
        glEnableVertexAttribArray(SHADER_UV_INDEX);
        glEnableVertexAttribArray(SHADER_TID_INDEX);
        glEnableVertexAttribArray(SHADER_MID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
        glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::mask_uv)));
        glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
        glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::mid)));
        glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
		
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

		m_iboBuffer->release();
		m_vao.release();
		m_vboBuffer->release();
	}

    float BatchRenderer2D::submitTexture(uint textureID)
    {
        float result = 0.0f;
        bool found = false;
        for (uint i = 0; i < m_textureSlots.size(); i++)
        {
            if (m_textureSlots[i] == textureID)
            {
                result = (float)(i + 1);
                found = true;
                break;
            }
        }

        if (!found)
        {
            if (m_textureSlots.size() >= RENDERER_MAX_TEXTURES)
            {
                end();
                flush();
                begin();
            }
            m_textureSlots.push_back(textureID);
            result = static_cast<float>(m_textureSlots.size());
        }
        return result;
    }

    float BatchRenderer2D::submitTexture(const QSharedPointer<QOpenGLTexture>& texture)
    {
        return submitTexture(texture->textureId());
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
            ts = submitTexture(renderable->getTexture());
		}

        QMatrix4x4 maskTransform;
        const GLuint mid = (m_mask==nullptr) ? 0 : m_mask->texture->textureId();
        float ms = 0.0f;

        if (m_mask != nullptr)
        {
            maskTransform = m_mask->transform.inverted();
            ms = submitTexture(m_mask->texture);
        }

        QVector3D vertex = *m_tranformationBack * position;
        QVector3D tmpVertex = maskTransform * vertex;

        m_buffer->vertex = vertex;
		m_buffer->uv = UV[0];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
		m_buffer->tid = ts;
        m_buffer->mid = ms;
		m_buffer->color = color;
		m_buffer++;

        vertex = *m_tranformationBack * QVector3D(position.x(), position.y() + size.y(), position.z());
        tmpVertex = maskTransform * vertex;
		m_buffer->vertex = vertex;
		m_buffer->uv = UV[1];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
		m_buffer->tid = ts;
        m_buffer->mid = ms;
		m_buffer->color = color;
		m_buffer++;

        vertex = *m_tranformationBack * QVector3D(position.x() + size.x(), position.y() + size.y(), position.z());
        tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
		m_buffer->uv = UV[2];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
		m_buffer->color = color;
		m_buffer++;

        vertex = *m_tranformationBack * QVector3D(position.x() + size.x(), position.y(), position.z());
        tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
		m_buffer->uv = UV[3];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
		m_buffer->color = color;
		m_buffer++;

		m_indexCount += 6;
	}

	void BatchRenderer2D::drawString(const std::string& text, const QVector3D& position, QVector4D& color)
	{
		
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
		m_textureSlots.clear();
	}
	void BatchRenderer2D::end()
	{
		m_vboBuffer->unmap();
		m_vboBuffer->release();
	}
}