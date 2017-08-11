#ifndef CGFF_MESH_FACTORY_H
#define CGFF_MESH_FACTORY_H

#include "maths/qtmaths.h"
#include "utils/qtopengl.h"
#include "utils/types.h"
#include "mesh.h"
#include "material.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

namespace CGFF {
    namespace MeshFactory {

        struct Quad {
            QOpenGLBuffer vbuf;
            QOpenGLVertexArrayObject vao;
            VertexData data[4];   
            int count;

            Quad() {
                count = 6;
            }

            void create(QSharedPointer<QOpenGLShaderProgram>& shader, float x, float y, float width, float height) {
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

                vao.release();
                vbuf.release();
                shader->release();
            }

            void create(float x, float y, float width, float height) {
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

                GL->glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
                GL->glEnableVertexAttribArray(SHADER_UV_INDEX);
                GL->glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
                GL->glEnableVertexAttribArray(SHADER_TID_INDEX);
                GL->glEnableVertexAttribArray(SHADER_MID_INDEX);
                GL->glEnableVertexAttribArray(SHADER_COLOR_INDEX);

                GL->glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
                GL->glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
                GL->glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv)));
                GL->glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
                GL->glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid)));
                GL->glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

                vao.release();
                vbuf.release();            
            }
        };

        struct Cube {
        
            QOpenGLBuffer vboBuf, indexBuf;
            QOpenGLVertexArrayObject vao;
            Vertex data[8];
            QSharedPointer<Mesh> mesh;
            int count;
            Cube() {
                count = 36;
            }

            void create(QSharedPointer<QOpenGLShaderProgram>& shader, float size, QSharedPointer<MaterialInstance>& material)
            {
                data[0].position = QVector3D(-size / 2.0f, -size / 2.0f, size / 2.0f);
                data[1].position = QVector3D(size / 2.0f, -size / 2.0f, size / 2.0f);
                data[2].position = QVector3D(size / 2.0f, size / 2.0f, size / 2.0f);
                data[3].position = QVector3D(-size / 2.0f, size / 2.0f, size / 2.0f);
                data[4].position = QVector3D(-size / 2.0f, -size / 2.0f, -size / 2.0f);
                data[5].position = QVector3D(size / 2.0f, -size / 2.0f, -size / 2.0f);
                data[6].position = QVector3D(size / 2.0f, size / 2.0f, -size / 2.0f);
                data[7].position = QVector3D(-size / 2.0f, size / 2.0f, -size / 2.0f);

                data[0].normal = QVector3D(-1.0f, -1.0f, 1.0f);
                data[1].normal = QVector3D(1.0f, -1.0f, 1.0f);
                data[2].normal = QVector3D(1.0f, 1.0f, 1.0f);
                data[3].normal = QVector3D(-1.0f, 1.0f, 1.0f);
                data[4].normal = QVector3D(-1.0f, -1.0f, -1.0f);
                data[5].normal = QVector3D(1.0f, -1.0f, -1.0f);
                data[6].normal = QVector3D(1.0f, 1.0f, -1.0f);
                data[7].normal = QVector3D(-1.0f, 1.0f, -1.0f);

                shader->bind();

                vao.create();
                vao.bind();

                vboBuf.create();
                vboBuf.bind();
                vboBuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
                vboBuf.allocate(data, sizeof(Vertex) * 8);

                //To do: need to be updated
                int position = shader->attributeLocation("position");
                int normal = shader->attributeLocation("normal");
                int uv = shader->attributeLocation("uv");

                shader->enableAttributeArray(position);
                shader->enableAttributeArray(normal);
                shader->enableAttributeArray(uv);

                shader->setAttributeBuffer(position, GL_FLOAT, 0, 3, sizeof(Vertex));
                shader->setAttributeBuffer(normal, GL_FLOAT, offsetof(Vertex, normal), 3, sizeof(Vertex));
                shader->setAttributeBuffer(uv, GL_FLOAT, offsetof(Vertex, uv), 2, sizeof(Vertex));

                uint indices[36] =
                {
                    0, 1, 2, 2, 3, 0,
                    3, 2, 6, 6, 7, 3,
                    7, 6, 5, 5, 4, 7,
                    4, 0, 3, 3, 7, 4,
                    0, 1, 5, 5, 4, 0,
                    1, 5, 6, 6, 2, 1
                };

                indexBuf = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
                indexBuf.create();
                indexBuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
                indexBuf.bind();
                indexBuf.allocate(indices, count* sizeof(uint));
                indexBuf.release();

                vao.release();
                shader->release();

                mesh = QSharedPointer<Mesh>(new Mesh(&vao, &indexBuf, material));
            }
            
        };

        struct Plane
        {
            QOpenGLBuffer vboBuf, indexBuf;
            QOpenGLVertexArrayObject vao;
            Vertex data[4];
            QSharedPointer<Mesh> mesh;

            void create(float width, float height, const QVector3D& normal, QSharedPointer<MaterialInstance>& material)
            {
                QVector3D vec = normal * 90.0f;
               
                QMatrix4x4 rotation;
                rotation.rotate(vec.x(), QVector3D(0, 0, 1));
                rotation.rotate(vec.y(), QVector3D(0, 1, 0));
                rotation.rotate(vec.z(), QVector3D(1, 0, 0));

                data[0].position = rotation * QVector3D(-width / 2.0f, 0.0f, -height / 2.0f);
                data[0].normal = normal;

                data[1].position = rotation * QVector3D(-width / 2.0f, 0.0f, height / 2.0f);
                data[1].normal = normal;

                data[2].position = rotation * QVector3D(width / 2.0f, 0.0f, height / 2.0f);
                data[2].normal = normal;

                data[3].position = rotation * QVector3D(width / 2.0f, 0.0f, -height / 2.0f);
                data[3].normal = normal;

                vao.create();
                vao.bind();

                vboBuf.create();
                vboBuf.bind();
                vboBuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
                vboBuf.allocate(data, RENDERER_VERTEX_SIZE * 4);
      
                GL->glEnableVertexAttribArray(0);//position
                GL->glEnableVertexAttribArray(1);//normal
                GL->glEnableVertexAttribArray(2);//uv

                //position
                GL->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
                //normal
                GL->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, normal)));
                //uv
                GL->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, uv)));
            
                uint indices[36] =
                {
                    0, 1, 2,
                    2, 3, 0
                };

                indexBuf = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
                indexBuf.create();
                indexBuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
                indexBuf.bind();
                indexBuf.allocate(indices, 6 * sizeof(uint));
                indexBuf.release();

                vao.release();
                vboBuf.release();

                mesh = QSharedPointer<Mesh>(new Mesh(&vao, &indexBuf, material));
            }
        };
    }
}

#endif
