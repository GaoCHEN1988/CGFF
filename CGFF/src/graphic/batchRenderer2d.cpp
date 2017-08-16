#include "batchRenderer2d.h"
#include "meshFactory.h"

#include "api/vertexBuffer.h"
#include "api/layoutBuffer.h"
#include "renderer.h"
#include "shader/shaderFactory.h"

namespace CGFF {

	const uint g_RequiredSystemUniformsCount = 2;
	const QStringList g_RequiredSystemUniforms =
	{
		"sys_ProjectionMatrix",
		"sys_ViewMatrix"
	};

	const uint sys_ProjectionMatrixIndex = 0;
	const uint sys_ViewMatrixIndex = 1;

	BatchRenderer2D::BatchRenderer2D(const QSize& screenSize)
		: Renderer2D()
		, m_indexCount(0)
        , m_viewportSize(screenSize)
        , m_screenSize(screenSize)
        , m_screenBuffer(0)
		, m_indices(nullptr)
	{
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		//m_vao.destroy();
		//m_vboBuffer->destroy();
		//m_iboBuffer->destroy();

		//delete m_vboBuffer;
		//delete m_iboBuffer;

		if (m_indices)
			delete[] m_indices;
	}

	//void BatchRenderer2D::init()
	//{
	//	m_vao.create();
	//	m_vao.bind();
	//	
	//	m_vboBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	//	m_vboBuffer->create();
	//	m_vboBuffer->bind();
	//	m_vboBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
	//	m_vboBuffer->allocate(NULL, RENDERER_BUFFER_SIZE);
	//	
	//	GL->glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
 //       GL->glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
 //       GL->glEnableVertexAttribArray(SHADER_UV_INDEX);
 //       GL->glEnableVertexAttribArray(SHADER_TID_INDEX);
 //       GL->glEnableVertexAttribArray(SHADER_MID_INDEX);
	//	GL->glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	//	GL->glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	//	GL->glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
 //       GL->glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::mask_uv)));
 //       GL->glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
 //       GL->glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::mid)));
 //       GL->glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
	//	
	//	GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
	//	int offset = 0;
	//	for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6)
	//	{
	//		indices[i] = offset + 0;
	//		indices[i + 1] = offset + 1;
	//		indices[i + 2] = offset + 2;
	//		indices[i + 3] = offset + 2;
	//		indices[i + 4] = offset + 3;
	//		indices[i + 5] = offset + 0;
	//		offset += 4;
	//	}
	//	m_iboBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	//	m_iboBuffer->create();
	//	m_iboBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
	//	m_iboBuffer->bind();
	//	m_iboBuffer->allocate(indices, RENDERER_INDICES_SIZE* sizeof(GLuint));
	//	m_indexCount = 0;
	//	m_iboBuffer->release();
	//	m_vao.release();
	//	m_vboBuffer->release();
 //       //set frame buffer
 //       m_format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
 //       //m_format.setSamples(8);
 //       glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_screenBuffer);
 //       m_frameBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize, m_format));
 //       //m_frameBuffer->addColorAttachment(m_viewportSize);
 //       m_framebufferShader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);
 //       // load and compile vertex shader
 //       bool success = m_framebufferShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shaders/fbVertexShader.vert");
 //       // load and compile fragment shader
 //       success = m_framebufferShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shaders/fbfragmentShader.frag");
 //       m_framebufferShader->link();
 //       m_framebufferShader->bind();
 //       QMatrix4x4 proj = QMatrix4x4();
 //       proj.ortho(0, (float)m_screenSize.width(), (float)m_screenSize.height(), 0, -1.0f, 100.0f);
 //       m_framebufferShader->setUniformValue("projMatrix", proj);
 //       m_framebufferShader->setUniformValue("tex", 0);
 //       m_framebufferShader->release();
 //       m_screenQuad.create(m_framebufferShader, 0, 0, (float)m_screenSize.width(), (float)m_screenSize.height());
 //       m_postEffects = QSharedPointer<PostEffects>(new PostEffects());
 //       m_postEffectsBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize, m_format));
 //       //m_postEffectsBuffer->addColorAttachment(m_viewportSize);
 //       //!!Important
 //       m_frameBuffer->release();
 //       m_postEffectsBuffer->release();
	//}

	void BatchRenderer2D::init()
	{
		m_postEffectsEnabled = false;

		m_systemUniforms.resize(g_RequiredSystemUniformsCount);

		m_shader = BatchRendererShader();

		const ShaderUniformBufferList& vssu = m_shader->getVSSystemUniforms();
		Q_ASSERT(vssu.size());
		for (uint i = 0; i < vssu.size(); i++)
		{
			QSharedPointer<ShaderUniformBufferDeclaration> ub = vssu[i];
			UniformBuffer buffer(QSharedPointer<uchar>(new uchar[ub->getSize()]), ub->getSize());

			m_systemUniformBuffers.push_back(buffer);
			for (QSharedPointer<ShaderUniformDeclaration> decl : ub->getUniformDeclarations())
			{
				for (uint j = 0; j < g_RequiredSystemUniformsCount; j++)
				{
					if (decl->getName() == g_RequiredSystemUniforms[j])
						m_systemUniforms[j] = BR2DSystemUniform(buffer, decl->getOffset());
				}
			}
		}

		QMatrix4x4 proj = QMatrix4x4();
		proj.ortho(0, (float)m_screenSize.width(), (float)m_screenSize.height(), 0, -1.0f, 100.0f);

		setCamera(QSharedPointer<Camera>(new Camera(proj)));

		m_shader->bind();
		m_vertexArray = VertexArray::create();
		m_vertexArray->bind();

		QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::DYNAMIC);
		buffer->resize(RENDERER_BUFFER_SIZE);
		LayoutBuffer layout;
		layout.push<QVector3D>("POSITION"); // Position
		layout.push<QVector2D>("TEXCOORD"); // UV
		layout.push<QVector2D>("MASKUV"); // Mask UV
		layout.push<float>("ID"); // Texture Index
		layout.push<float>("MASKID"); // Mask Index
		//test
		layout.push<QVector4D>("COLOR", 4, true); // Color
		buffer->setLayout(layout);
		
		m_vertexArray->pushBuffer(buffer);

		if (m_indices)
			delete[] m_indices;

		m_indices = new GLuint[RENDERER_INDICES_SIZE];

		int offset = 0;

		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			m_indices[i] = offset + 0;
			m_indices[i + 1] = offset + 1;
			m_indices[i + 2] = offset + 2;
			m_indices[i + 3] = offset + 2;
			m_indices[i + 4] = offset + 3;
			m_indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_indexBuffer = IndexBuffer::create(m_indices, RENDERER_INDICES_SIZE);
		m_vertexArray->unBind();

		m_indexCount = 0;

		//delete[] indices;

#ifdef FRAMEBUDDER_TEST
		//set frame buffer
		m_format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
		//m_format.setSamples(8);
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_screenBuffer);
		m_frameBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize, m_format));
		//m_frameBuffer->addColorAttachment(m_viewportSize);
		m_framebufferShader = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram);
		// load and compile vertex shader
		bool success = m_framebufferShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "src/graphic/shaders/fbVertexShader.vert");
		// load and compile fragment shader
		success = m_framebufferShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "src/graphic/shaders/fbfragmentShader.frag");
		m_framebufferShader->link();
		m_framebufferShader->bind();
		QMatrix4x4 proj = QMatrix4x4();
		proj.ortho(0, (float)m_screenSize.width(), (float)m_screenSize.height(), 0, -1.0f, 100.0f);
		m_framebufferShader->setUniformValue("projMatrix", proj);
		m_framebufferShader->setUniformValue("tex", 0);
		m_framebufferShader->release();

		m_screenQuad.create(m_framebufferShader, 0, 0, (float)m_screenSize.width(), (float)m_screenSize.height());

		m_postEffects = QSharedPointer<PostEffects>(new PostEffects());
		m_postEffectsBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize, m_format));
		//m_postEffectsBuffer->addColorAttachment(m_viewportSize);

		//!!Important
		m_frameBuffer->release();
		m_postEffectsBuffer->release();
#endif
	}

	/*
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

	*/

	float BatchRenderer2D::submitTexture(const QSharedPointer<Texture>& texture)
	{
		float result = 0.0f;
		bool found = false;

		for (uint i = 0; i < m_textures.size(); i++)
		{
			if (m_textures[i] == texture)
			{
				result = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_textures.size() >= RENDERER_MAX_TEXTURES)
			{
				end();
				flush();
				begin();
			}
			m_textures.push_back(texture);
			result = static_cast<float>(m_textures.size());
		}
		return result;
	}

	void BatchRenderer2D::begin()
	{
        if (m_renderTarget == RenderTarget::BUFFER)
        {
#ifdef FRAMEBUDDER_TEST
            if (m_viewportSize != m_frameBuffer->size())
            {
                m_frameBuffer.clear();
                m_frameBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize));
                m_postEffectsBuffer.clear();
                m_postEffectsBuffer = QSharedPointer<QOpenGLFramebufferObject>(new QOpenGLFramebufferObject(m_viewportSize));
            }

            if (m_postEffectsEnabled)
            {
                m_postEffectsBuffer->bind();
                GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }

            m_frameBuffer->bind();
            GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //GL->glBlendFunc(GL_ONE, GL_ZERO);

#endif
        }
        else
        {
            //GL->glBindFramebuffer(GL_FRAMEBUFFER, m_screenBuffer);
            //glViewport(0, 0, m_screenSize.width(), m_screenSize.height());
			Renderer::setViewport(0, 0, m_screenSize.width(), m_screenSize.height());
        }

		//m_vboBuffer->bind();
		//m_buffer = (VertexData*)m_vboBuffer->map(QOpenGLBuffer::WriteOnly);

		m_vertexArray->bind();
		m_buffer = m_vertexArray->getBuffer()->getPointer<VertexData>();
	}

	void BatchRenderer2D::submit(QSharedPointer<Renderable2D>& renderable)
	{
        if (!renderable->isVisible())
            return;

		const QVector3D& position = renderable->getPosition();
		const QVector2D& size = renderable->getSize();
		const QVector4D& color = renderable->getColor();
		const QVector<QVector2D>& UV = renderable->getUV();
		//const GLuint textureId = renderable->getTextureID();
		const QSharedPointer<Texture> texture = renderable->getTexture();

		float ts = 0.0;

		if (texture)
		{
            ts = submitTexture(renderable->getTexture());
		}

        QMatrix4x4 maskTransform;
		//const GLuint mid = (m_mask == nullptr) ? 0 : m_mask->texture->textureId();
		const GLuint mid = (m_mask==nullptr) ? 0 : submitTexture(m_mask->texture);
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

		//vertex = *m_tranformationBack * QVector3D(position.x(), position.y() + size.y(), position.z());
		vertex = *m_tranformationBack * QVector3D(position.x() + size.x(), position.y(), position.z());
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

        vertex = *m_tranformationBack * QVector3D(position.x(), position.y() + size.y(), position.z());
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

    void BatchRenderer2D::drawString(QString text, const QVector3D& position, int width, int height, QVector4D& color, QFont font)
    {
        //Test
        int size = font.pixelSize();
        int width_ = size * 5;
        int height_ = size;

        // create the QImage and draw txt into it
        QImage textimg(width, height, QImage::Format_ARGB32);
        {
            QPainter painter(&textimg);
            textimg.fill(Qt::transparent);
            painter.setBrush(QColor(color.x() * 255, color.y() * 255, color.z() * 255, color.w() * 255));
            painter.setPen(QColor(color.x() * 255, color.y() * 255, color.z() * 255, color.w() * 255));
            font.setPixelSize(height);
            painter.setFont(font);
            painter.drawText(0, height-10, text);
        }

        QSharedPointer<Texture> strTexture = Texture2D::createFromImage(textimg);

        m_strTextures.append(strTexture);
        
        float ts = 0.0f;
        ts = submitTexture(strTexture);

        QVector3D vertex = *m_tranformationBack * position;

        m_buffer->vertex = *m_tranformationBack * position;
        m_buffer->uv = QVector2D(0, 0);
        m_buffer->tid = ts;
        m_buffer->color = color;
        m_buffer++;

        m_buffer->vertex = *m_tranformationBack * QVector3D(position.x()+ width, position.y(), position.z());
        m_buffer->uv = QVector2D(0, 1);
        m_buffer->tid = ts;
        m_buffer->color = color;
        m_buffer++;

        m_buffer->vertex = *m_tranformationBack * QVector3D(position.x() + width, position.y() + height, position.z());
        m_buffer->uv = QVector2D(1, 1);
        m_buffer->tid = ts;
        m_buffer->color = color;
        m_buffer++;

        m_buffer->vertex = *m_tranformationBack * QVector3D(position.x(), position.y() + height, position.z());
        m_buffer->uv = QVector2D(1, 0);
        m_buffer->tid = ts;
        m_buffer->color = color;
        m_buffer++;

        m_indexCount += 6;

    }
	
    void BatchRenderer2D::flush() 
	{
        //GL->glDepthFunc(GL_NEVER);
        //GL->glDisable(GL_DEPTH_TEST);
		Renderer::setDepthTesting(false);

		//for (int i = 0; i < m_textureSlots.size(); i++)
		//{
  //          GL->glActiveTexture(GL_TEXTURE0 + i);
  //          GL->glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
		//}

		m_shader->bind();
		for (uint i = 0; i < m_systemUniformBuffers.size(); i++)
			m_shader->setPSSystemUniformBuffer(m_systemUniformBuffers[i].buffer_pointer.data(), m_systemUniformBuffers[i].size, i);

		for (uint i = 0; i < m_textures.size(); i++)
			m_textures[i]->bind(i);

		//m_vao.bind();
		//m_iboBuffer->bind();
  //      GL->glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);
		//m_iboBuffer->release();
		//m_vao.release();
		//m_vboBuffer->release();
		//m_indexCount = 0;
		//m_textureSlots.clear();

		m_vertexArray->bind();
		m_indexBuffer->bind();
		m_vertexArray->draw(m_indexCount);
		m_indexBuffer->unBind();
		m_vertexArray->unBind();

		for (uint i = 0; i < m_textures.size(); i++)
			m_textures[i]->unBind(i);

		m_indexCount = 0;
		m_textures.clear();

#ifdef FRAMEBUDDER_TEST
        if (m_renderTarget == RenderTarget::BUFFER)
        {
            // Post Effects pass should go here!
            if (m_postEffectsEnabled)
            {
                m_postEffects->renderPostEffects(m_frameBuffer, m_postEffectsBuffer, m_screenQuad.vao, m_iboBuffer);
            }

            // Display Framebuffer - potentially move to Framebuffer class
            GL->glBindFramebuffer(GL_FRAMEBUFFER, m_screenBuffer);
            //glViewport(0, 0, m_screenSize.width(), m_screenSize.height());
            //GL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            m_framebufferShader->bind();

            //Need to test
            GL->glActiveTexture(GL_TEXTURE0);

            if (m_postEffectsEnabled)
				GL->glBindTexture(GL_TEXTURE_2D, m_postEffectsBuffer->texture());
            else
				GL->glBindTexture(GL_TEXTURE_2D, m_frameBuffer->texture());

            m_screenQuad.vao.bind();

            m_iboBuffer->bind();
            GL->glDrawElements(GL_TRIANGLES, m_screenQuad.count, GL_UNSIGNED_INT, NULL);
            m_iboBuffer->release();

            m_screenQuad.vao.release();
            m_framebufferShader->release();
            m_iboBuffer->release();
        }
        GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_frameBuffer->release();
        m_postEffectsBuffer->release();
#endif

		m_strTextures.clear();

	}

	void BatchRenderer2D::end()
	{
		m_vertexArray->getBuffer()->releasePointer();
		m_vertexArray->unBind();
	}

	void BatchRenderer2D::setCamera(QSharedPointer<Camera> camera)
	{
		m_camera = camera;

		memcpy(m_systemUniforms[sys_ProjectionMatrixIndex].buffer.buffer_pointer.data() + m_systemUniforms[sys_ProjectionMatrixIndex].offset, &camera->getProjectionMatrix(), sizeof(QMatrix4x4));
		memcpy(m_systemUniforms[sys_ViewMatrixIndex].buffer.buffer_pointer.data() + m_systemUniforms[sys_ViewMatrixIndex].offset, &camera->getViewMatrix(), sizeof(QMatrix4x4));
	}

    void BatchRenderer2D::drawLine(float x0, float y0, float x1, float y1, QVector4D color, float thickness)
    {
        const QVector<QVector2D>& uv = Renderable2D::getDefaultUVs();
        float ts = 0.0f;

        QMatrix4x4 maskTransform;
		const GLuint mid = (m_mask == nullptr) ? 0 : submitTexture(m_mask->texture);
        float ms = 0.0f;

        if (m_mask != nullptr)
        {
            maskTransform = m_mask->transform.inverted();
            ms = submitTexture(m_mask->texture);
        }

        QVector2D normal = QVector2D(y1 - y0, -(x1 - x0)).normalized() * thickness;
        QVector3D vertex = *m_tranformationBack * QVector3D(x0 + normal.x(), y0 + normal.y(), 0.0f);
        QVector3D tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
        m_buffer->uv = uv[0];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
        m_buffer->color = color;
        m_buffer++;

        vertex = *m_tranformationBack * QVector3D(x1 + normal.x(), y1 + normal.y(), 0.0f);
        tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
        m_buffer->uv = uv[1];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
        m_buffer->color = color;
        m_buffer++;

        vertex = *m_tranformationBack * QVector3D(x1 - normal.x(), y1 - normal.y(), 0.0f);
        tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
        m_buffer->uv = uv[2];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
        m_buffer->color = color;
        m_buffer++;

        vertex = *m_tranformationBack * QVector3D(x0 - normal.x(), y0 - normal.y(), 0.0f);
        tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
        m_buffer->uv = uv[3];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
        m_buffer->color = color;
        m_buffer++;

        m_indexCount += 6;
    }

    void BatchRenderer2D::drawLine(const QVector2D& start, const QVector2D& end, QVector4D color, float thickness)
    {
        drawLine(start.x(), start.y(), end.x(), end.y(), color, thickness);
    }

    void BatchRenderer2D::drawRect(float x, float y, float width, float height, QVector4D color, float thickness)
    {
        drawLine(x, y, x + width, y, color, thickness);
        drawLine(x + width, y, x + width, y + height, color, thickness);
        drawLine(x + width, y + height, x, y + height, color, thickness);
        drawLine(x, y + height, x, y, color, thickness);
    }

    void BatchRenderer2D::drawRect(const QRect& rectangle, QVector4D color)
    {
        drawRect(rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height(), color);
    }

    void BatchRenderer2D::fillRect(float x, float y, float width, float height, QVector4D color)
    {
        QVector3D position(x, y, 0.0f);
        QVector2D size(width, height);
        const QVector<QVector2D>& uv = Renderable2D::getDefaultUVs();
        float ts = 0.0f;

        QMatrix4x4 maskTransform;
		const GLuint mid = (m_mask == nullptr) ? 0 : submitTexture(m_mask->texture);
        float ms = 0.0f;

        if (m_mask != nullptr)
        {
            maskTransform = m_mask->transform.inverted();
            ms = submitTexture(m_mask->texture);
        }

        QVector3D vertex = *m_tranformationBack * position;
        QVector3D tmpVertex = maskTransform * vertex;

        m_buffer->vertex = vertex;
        m_buffer->uv = uv[0];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
        m_buffer->color = color;
        m_buffer++;

        vertex = *m_tranformationBack * QVector3D(position.x() + size.x(), position.y() , position.z());
        tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
        m_buffer->uv = uv[1];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
        m_buffer->color = color;
        m_buffer++;

        vertex = *m_tranformationBack * QVector3D(position.x() + size.x(), position.y() + size.y(), position.z());
        tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
        m_buffer->uv = uv[2];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
        m_buffer->color = color;
        m_buffer++;

        vertex = *m_tranformationBack * QVector3D(position.x(), position.y() + size.y(), position.z());
        tmpVertex = maskTransform * vertex;
        m_buffer->vertex = vertex;
        m_buffer->uv = uv[3];
        m_buffer->mask_uv = QVector2D(tmpVertex.x(), tmpVertex.y());
        m_buffer->tid = ts;
        m_buffer->mid = ms;
        m_buffer->color = color;
        m_buffer++;

        m_indexCount += 6;
    }

    void BatchRenderer2D::fillRect(const QRect& rectangle, QVector4D color)
    {
        fillRect(rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height(), color);
    }
}