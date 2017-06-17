#include "batchRenderer2d.h"
#include "meshFactory.h"

namespace CGFF {

	BatchRenderer2D::BatchRenderer2D(const QSize& screenSize)
		: Renderer2D()
		, m_indexCount(0)
        , m_viewportSize(screenSize)
        , m_screenSize(screenSize)
        , m_screenQuad(0)
        , m_screenBuffer(0)
        , m_strTexture(nullptr)
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

        //set frame buffer
        /*m_format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_format.setSamples(4);*/
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_screenBuffer);
        m_frameBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize, m_format));
        //m_frameBuffer->addColorAttachment(m_viewportSize);
        m_framebufferShader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);
        // load and compile vertex shader
        bool success = m_framebufferShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shader/fbVertexShader.vert");
        // load and compile fragment shader
        success = m_framebufferShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shader/fbfragmentShader.frag");
        m_framebufferShader->link();
        m_framebufferShader->bind();
        QMatrix4x4 proj = QMatrix4x4();
        proj.ortho(0, (float)m_screenSize.width(), (float)m_screenSize.height(), 0, -1.0f, 1.0f);
        m_framebufferShader->setUniformValue("projMatrix", proj);
        m_framebufferShader->setUniformValue("tex", 0);
        //m_screenQuad = MeshFactory::CreateQuad(0, 0, (float)m_screenSize.width(), (float)m_screenSize.height());
        m_framebufferShader->release();

        createQuad(0, 0, (float)m_screenSize.width(), (float)m_screenSize.height());

        m_postEffects = QSharedPointer<PostEffects>(new PostEffects());
        m_postEffectsBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize, m_format));
        //m_postEffectsBuffer->addColorAttachment(m_viewportSize);
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

    void BatchRenderer2D::createQuad(float x, float y, float width, float height)
    {
        VertexData data[4];
        data[0].vertex = QVector3D(x, y, 0);
        data[0].uv = QVector2D(0, 1);

        data[1].vertex = QVector3D(x, y + height, 0);
        data[1].uv = QVector2D(0, 0);

        data[2].vertex = QVector3D(x + width, y + height, 0);
        data[2].uv = QVector2D(1, 0);

        data[3].vertex = QVector3D(x + width, y, 0);
        data[3].uv = QVector2D(1, 1);

        vao.create();
        vao.bind();

        vbuf.create();
        vbuf.bind();
        vbuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        vbuf.allocate(data, RENDERER_VERTEX_SIZE * 4);

        glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
        glEnableVertexAttribArray(SHADER_UV_INDEX);
        glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
        glEnableVertexAttribArray(SHADER_TID_INDEX);
        glEnableVertexAttribArray(SHADER_MID_INDEX);
        glEnableVertexAttribArray(SHADER_COLOR_INDEX);

        glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
        glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
        glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv)));
        glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
        glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid)));
        glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

        vao.release();
        vbuf.release();
    }

	void BatchRenderer2D::begin()
	{
        if (m_renderTarget == RenderTarget::BUFFER)
        {
            if (m_viewportSize != m_frameBuffer->size())
            {
                m_frameBuffer.clear();
                m_frameBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize));

                //if (m_postEffectsEnabled)
                //{
                //    m_postEffectsBuffer.clear();
                //    m_postEffectsBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize));
                //}
            }


            //if (m_postEffectsEnabled)
            //{
            //    m_postEffectsBuffer->bind();
            //}

            m_frameBuffer->bind();

            //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_screenBuffer);
            //glViewport(0, 0, m_screenSize.width(), m_screenSize.height());
        }

		m_vboBuffer->bind();
		m_buffer = (VertexData*)m_vboBuffer->map(QOpenGLBuffer::WriteOnly);
	}

	void BatchRenderer2D::submit(QSharedPointer<Renderable2D> renderable)
	{
		const QVector3D& position = renderable->getPosition();
		const QVector2D& size = renderable->getSize();
		const QVector4D& color = renderable->getColor();
		const QVector<QVector2D>& UV = renderable->getUV();
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
        int width = 2;
        int height = 1;

        // create the QImage and draw txt into it
        QImage textimg(width * 50, height * 50, QImage::Format_ARGB32);
        {
            QPainter painter(&textimg);
            textimg.fill(Qt::transparent);
            painter.setBrush(Qt::yellow);
            painter.setPen(Qt::yellow);
            painter.setFont(QFont("Sans", 20));
            painter.drawText(5, 30, QString::fromStdString(text));
        }

        m_strTexture = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(textimg.mirrored()));

        float ts = 0.0f;
        ts = submitTexture(m_strTexture->textureId());

        QVector3D vertex = *m_tranformationBack * position;

        m_buffer->vertex = *m_tranformationBack * position;
        m_buffer->uv = QVector2D(0, 0);
        m_buffer->tid = ts;
        m_buffer->color = color;
        m_buffer++;

        m_buffer->vertex = *m_tranformationBack * QVector3D(position.x(), position.y() + height, position.z());
        m_buffer->uv = QVector2D(0, 1);
        m_buffer->tid = ts;
        m_buffer->color = color;
        m_buffer++;

        m_buffer->vertex = *m_tranformationBack * QVector3D(position.x()+ width, position.y() + height, position.z());
        m_buffer->uv = QVector2D(1, 1);
        m_buffer->tid = ts;
        m_buffer->color = color;
        m_buffer++;

        m_buffer->vertex = *m_tranformationBack * QVector3D(position.x() + width, position.y(), position.z());
        m_buffer->uv = QVector2D(1, 0);
        m_buffer->tid = ts;
        m_buffer->color = color;
        m_buffer++;

        m_indexCount += 6;

	}
	void BatchRenderer2D::flush() 
	{
        ////test
        //if (m_postEffectsEnabled)
        //{
        //    m_postEffectsBuffer->bind();
        //}
        //m_frameBuffer->bind();
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        if (m_postEffectsEnabled)
        {
            m_postEffectsBuffer->release();
            //m_postEffectsBuffer->toImage().save("testPost.png");
        }

        m_frameBuffer->release();
       // m_frameBuffer->toImage().save("testPost2.png");

        if (m_renderTarget == RenderTarget::BUFFER)
        {
            // Post Effects pass should go here!
            if (m_postEffectsEnabled)
            {
                m_postEffects->renderPostEffects(m_frameBuffer, m_postEffectsBuffer, m_vao, m_iboBuffer);
            }
            else
            {
                //// Display Framebuffer - potentially move to Framebuffer class
                //glBindFramebuffer(GL_FRAMEBUFFER, m_screenBuffer);
                //glViewport(0, 0, m_screenSize.width(), m_screenSize.height());
                //Need to test
                glActiveTexture(GL_TEXTURE0);

                if (m_postEffectsEnabled)
                    glBindTexture(GL_TEXTURE_2D, m_postEffectsBuffer->texture());
                else
                    glBindTexture(GL_TEXTURE_2D, m_frameBuffer->texture());
                
                vao.bind();

                m_framebufferShader->bind();
                //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //QImage image1 = m_postEffectsBuffer->toImage();

                //image1.save(QString("fb1.png"));

                //glBindVertexArray(m_screenQuad);
                m_iboBuffer->bind();
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
                m_iboBuffer->release();
                //glBindVertexArray(0);
                vao.release();
                m_framebufferShader->release();
            }
        }

        m_strTexture.clear();
	}

	void BatchRenderer2D::end()
	{
		m_vboBuffer->unmap();
		m_vboBuffer->release();
        //m_frameBuffer->release();
        //m_postEffectsBuffer->release();
	}
}