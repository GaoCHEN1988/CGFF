#include "meshFactory.h"
#include "../utils/types.h"
#include "renderable2d.h"

namespace CGFF {
    namespace MeshFactory {
       
        GLuint CreateQuad(float x, float y, float width, float height)
        {
            QOpenGLFunctions_4_4_Core gl;
            gl.initializeOpenGLFunctions();

            GLuint result;
            VertexData data[4];
            data[0].vertex = QVector3D(x, y, 0);
            data[0].uv = QVector2D(0, 1);

            data[1].vertex = QVector3D(x, y + height, 0);
            data[1].uv = QVector2D(0, 0);

            data[2].vertex = QVector3D(x + width, y + height, 0);
            data[2].uv = QVector2D(1, 0);

            data[3].vertex = QVector3D(x + width, y, 0);
            data[3].uv = QVector2D(1, 1);

            GLuint buffer;
            gl.glGenVertexArrays(1, &result);
            gl.glGenBuffers(1, &buffer);

            gl.glBindVertexArray(result);
            gl.glBindBuffer(GL_ARRAY_BUFFER, buffer);
            gl.glBufferData(GL_ARRAY_BUFFER, RENDERER_VERTEX_SIZE * 4, data, GL_DYNAMIC_DRAW);

            gl.glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            gl.glEnableVertexAttribArray(SHADER_UV_INDEX);
            gl.glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
            gl.glEnableVertexAttribArray(SHADER_TID_INDEX);
            gl.glEnableVertexAttribArray(SHADER_MID_INDEX);
            gl.glEnableVertexAttribArray(SHADER_COLOR_INDEX);

            gl.glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
            gl.glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
            gl.glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv)));
            gl.glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
            gl.glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid)));
            gl.glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

            gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
            gl.glBindVertexArray(0);

            return result;
        }

        GLuint CreateQuad(const QVector2D& position, const QVector2D& size)
        {
            return CreateQuad(position.x(), position.y(), size.x(), size.y());
        }

    }
}