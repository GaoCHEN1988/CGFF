#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include "../maths/qtmaths.h"
#include "../utils/qtopengl.h"
#include "../utils/types.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

namespace CGFF {
    namespace MeshFactory {


        GLuint CreateQuad(float x, float y, float width, float height);
        GLuint CreateQuad(const QVector2D& position, const QVector2D& size);

        struct Quad {
            QOpenGLBuffer vbuf, nbuf;
            QOpenGLVertexArrayObject vao;
            VertexData data[4];        

            Quad() {
                
            }

            void load(QSharedPointer<QOpenGLShaderProgram>& shader, float x, float y, float width, float height) {
                data[0].vertex = QVector3D(x, y, 0);
                data[0].uv = QVector2D(0, 1);

                data[1].vertex = QVector3D(x, y + height, 0);
                data[1].uv = QVector2D(0, 0);

                data[2].vertex = QVector3D(x + width, y + height, 0);
                data[2].uv = QVector2D(1, 0);

                data[3].vertex = QVector3D(x + width, y, 0);
                data[3].uv = QVector2D(1, 1);

                shader->bind();

                vao.create();
                vao.bind();

                vbuf.create();
                vbuf.bind();
                vbuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
                vbuf.allocate(data, RENDERER_VERTEX_SIZE * 4);

                shader->enableAttributeArray(SHADER_VERTEX_INDEX);
                shader->enableAttributeArray(SHADER_UV_INDEX);
                shader->enableAttributeArray(SHADER_MASK_UV_INDEX);
                shader->enableAttributeArray(SHADER_TID_INDEX);
                shader->enableAttributeArray(SHADER_MID_INDEX);
                shader->enableAttributeArray(SHADER_COLOR_INDEX);

                shader->setAttributeBuffer(SHADER_VERTEX_INDEX, GL_FLOAT, 0, 3, RENDERER_VERTEX_SIZE);
                shader->setAttributeBuffer(SHADER_UV_INDEX, GL_FLOAT, offsetof(VertexData, uv), 2, RENDERER_VERTEX_SIZE);
                shader->setAttributeBuffer(SHADER_MASK_UV_INDEX, GL_FLOAT, offsetof(VertexData, mask_uv), 2, RENDERER_VERTEX_SIZE);
                shader->setAttributeBuffer(SHADER_TID_INDEX, GL_FLOAT, offsetof(VertexData, tid), 1, RENDERER_VERTEX_SIZE);
                shader->setAttributeBuffer(SHADER_MID_INDEX, GL_FLOAT, offsetof(VertexData, mid), 1, RENDERER_VERTEX_SIZE);
                shader->setAttributeBuffer(SHADER_COLOR_INDEX, GL_UNSIGNED_BYTE, offsetof(VertexData, color), 4, RENDERER_VERTEX_SIZE);

                /*glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
                glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
                glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv)));
                glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
                glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid)));
                glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));*/
                vao.release();
                vbuf.release();            
                shader->release();
            }
        };

    }
}

#endif
