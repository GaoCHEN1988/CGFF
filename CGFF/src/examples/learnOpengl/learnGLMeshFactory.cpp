#include "learnGLMeshFactory.h"

namespace LearnGL {
    using namespace CGFF;

    QSharedPointer<Mesh> CreateCube(float size, QSharedPointer<MaterialInstance> material)
    {
        struct CubeVertex
        {
            QVector3D position;
        };

        CubeVertex data[8];

        data[0].position = QVector3D(-size / 2.0f, 0, size / 2.0f);
        data[1].position = QVector3D(size / 2.0f, 0, size / 2.0f);
        data[2].position = QVector3D(size / 2.0f, size, size / 2.0f);
        data[3].position = QVector3D(-size / 2.0f, size, size / 2.0f);
        data[4].position = QVector3D(-size / 2.0f, 0, -size / 2.0f);
        data[5].position = QVector3D(size / 2.0f, 0, -size / 2.0f);
        data[6].position = QVector3D(size / 2.0f, size, -size / 2.0f);
        data[7].position = QVector3D(-size / 2.0f, size, -size / 2.0f);
        QSharedPointer<VertexArray> va = VertexArray::create();
        va->bind();
        QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
        buffer->setData(8 * sizeof(CubeVertex), data);
        LayoutBuffer layout;

        layout.push<QVector3D>("position");
        buffer->setLayout(layout);

        va->pushBuffer(buffer);

        uint indices[36] =
        {
            0, 1, 2, 2, 3, 0,
            3, 2, 6, 6, 7, 3,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            0, 1, 5, 5, 4, 0,
            1, 5, 6, 6, 2, 1
        };

        QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 36);

        va->unBind();

        return QSharedPointer<Mesh>(new Mesh(va, ib, material));
    }

    QSharedPointer<Mesh> CreatePlane(float width, float height, const QVector3D& normal, QSharedPointer<MaterialInstance> material)
    {
        struct PlaneVertex
        {
            QVector3D position;
            QVector3D normal;
            QVector2D uv;
        };

        QVector3D vec = normal * 90.0f;

        QMatrix4x4 rotation;
        rotation.rotate(vec.x(), QVector3D(0, 0, 1));
        rotation.rotate(vec.y(), QVector3D(0, 1, 0));
        rotation.rotate(vec.z(), QVector3D(1, 0, 0));

        PlaneVertex data[4];
        memset(data, 0, 4 * sizeof(PlaneVertex));

        QMatrix4x4 tmpRotate;
        //
        data[0].position = rotation * QVector3D(-width / 2.0f, 0.0f, -height / 2.0f);
        data[0].normal = normal;
        data[0].uv = QVector2D(0.0f, 0.0f);

        //
        data[1].position = rotation * QVector3D(-width / 2.0f, 0.0f, height / 2.0f);
        data[1].normal = normal;
        data[1].uv = QVector2D(0.0f, 1.0f);

        //
        data[2].position = rotation * QVector3D(width / 2.0f, 0.0f, height / 2.0f);
        data[2].normal = normal;
        data[2].uv = QVector2D(1.0f, 1.0f);

        //
        data[3].position = rotation * QVector3D(width / 2.0f, 0.0f, -height / 2.0f);
        data[3].normal = normal;
        data[3].uv = QVector2D(1.0f, 0.0f);

        QSharedPointer<VertexArray> va = VertexArray::create();
        va->bind();
        QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
        buffer->setData(4 * sizeof(PlaneVertex), data);
        LayoutBuffer layout;
        layout.push<QVector3D>("POSITION");
        layout.push<QVector3D>("NORMAL");
        layout.push<QVector2D>("TEXCOORD");
        buffer->setLayout(layout);

        va->pushBuffer(buffer);

        uint indices[6] =
        {
            0, 1, 2,
            2, 3, 0
        };

        QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 6);

        va->unBind();

        return QSharedPointer<Mesh>(new Mesh(va, ib, material));
    }
}
