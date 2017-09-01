#include "glVertexArray.h"
#include "utils/qtopengl.h"

namespace CGFF {

    GLVertexArray::GLVertexArray()
    {
        m_glVertexArray.create();
    }

    GLVertexArray::~GLVertexArray()
    {

    }

    void GLVertexArray::pushBuffer(QSharedPointer<VertexBuffer> buffer)
    {
        m_buffers.push_back(buffer);
    }

    void GLVertexArray::bind()
    {
        m_glVertexArray.bind();
        if(!m_buffers.isEmpty())
		    m_buffers.front()->bind();
    }

    void GLVertexArray::unBind()
    {
        m_glVertexArray.release();
        if (!m_buffers.isEmpty())
		    m_buffers.front()->unBind();
    }

    void GLVertexArray::draw(uint count, DrawMode mode) const
    {
        GL->glDrawElements(toGlMode(mode), count, GL_UNSIGNED_INT, NULL);
    }

	GLenum GLVertexArray::toGlMode(DrawMode mode) const
	{
		switch (mode)
		{
		case DrawMode::POINTS:			return GL_POINTS;
		case DrawMode::LINES:			return GL_LINES;
		case DrawMode::LINE_LOOP:		return GL_LINE_LOOP;
		case DrawMode::LINE_STRIP:		return GL_LINE_STRIP;
		case DrawMode::TRIANGLES:		return GL_TRIANGLES;
		case DrawMode::TRIANGLE_STRIP:	return GL_TRIANGLE_STRIP;
		case DrawMode::TRIANGLE_FAN:	return GL_TRIANGLE_FAN;
		case DrawMode::QUADS:			return GL_QUADS;
		case DrawMode::QUAD_STRIP:		return GL_QUAD_STRIP;
		case DrawMode::POLYGON:			return GL_POLYGON;
		}
		return GL_TRIANGLES;
	}
}