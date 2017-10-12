#include "learnGLMeshFactory.h"

namespace LearnGL {
    using namespace CGFF;

    QSharedPointer<Mesh> CreateCube(float size, QSharedPointer<MaterialInstance> material)
    {
        struct CubeVertex
        {
            QVector3D position;
            QVector3D normal;
            QVector2D uv;
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

        data[0].normal = QVector3D(-1.0f, -1.0f, 1.0f);
        data[1].normal = QVector3D(1.0f, -1.0f, 1.0f);
        data[2].normal = QVector3D(1.0f, 1.0f, 1.0f);
        data[3].normal = QVector3D(-1.0f, 1.0f, 1.0f);
        data[4].normal = QVector3D(-1.0f, -1.0f, -1.0f);
        data[5].normal = QVector3D(1.0f, -1.0f, -1.0f);
        data[6].normal = QVector3D(1.0f, 1.0f, -1.0f);
        data[7].normal = QVector3D(-1.0f, 1.0f, -1.0f);

        data[0].uv = QVector2D(0.0f, 0.0f);
        data[1].uv = QVector2D(0.0f, 1.0f);
        data[2].uv = QVector2D(1.0f, 1.0f);
        data[3].uv = QVector2D(1.0f, 0.0f);
        data[4].uv = QVector2D(0.0f, 0.0f);
        data[5].uv = QVector2D(0.0f, 1.0f);
        data[6].uv = QVector2D(1.0f, 1.0f);
        data[7].uv = QVector2D(1.0f, 0.0f);


        QSharedPointer<VertexArray> va = VertexArray::create();
        va->bind();
        QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
        buffer->setData(8 * sizeof(CubeVertex), data);
        LayoutBuffer layout;

        layout.push<QVector3D>("position");
        layout.push<QVector3D>("normal");
        layout.push<QVector2D>("uv");
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
            QVector3D binormal;
            QVector3D tangent;
        };

        QVector3D vec = normal * 90.0f;

        QMatrix4x4 rotation;
        rotation.rotate(vec.x(), QVector3D(0, 0, 1));
        rotation.rotate(vec.y(), QVector3D(0, 1, 0));
        rotation.rotate(vec.z(), QVector3D(1, 0, 0));

        PlaneVertex data[6];
        memset(data, 0, 6 * sizeof(PlaneVertex));

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

        QVector3D tangent1, bitangent1;
        QVector3D tangent2, bitangent2;
        // triangle 1
        // ----------
        QVector3D edge1 = data[1].position - data[0].position;
        QVector3D edge2 = data[2].position - data[0].position;
        QVector2D deltaUV1 = data[1].uv - data[0].uv;
        QVector2D deltaUV2 = data[2].uv - data[0].uv;

        GLfloat f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());

        tangent1.setX(f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x()));
        tangent1.setY(f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y()));
        tangent1.setZ(f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z()));
        tangent1.normalize();

        bitangent1.setX( f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x()));
        bitangent1.setY(f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y()));
        bitangent1.setZ(f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z()));
        bitangent1.normalize();

        // triangle 2
        // ----------
        edge1 = data[2].position - data[0].position;
        edge2 = data[3].position - data[0].position;
        deltaUV1 = data[2].uv - data[0].uv;
        deltaUV2 = data[3].uv - data[0].uv;

        f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());

        tangent2.setX(f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x()));
        tangent2.setY(f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y()));
        tangent2.setZ(f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z()));
        tangent2.normalize();

        bitangent2.setX( f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x()));
        bitangent2.setY(f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y()));
        bitangent2.setZ(f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z()));
        bitangent2.normalize();

        data[0].binormal = bitangent1;
        data[0].tangent = tangent1;

        data[1].binormal = bitangent1;
        data[1].tangent = tangent1;

        data[2].binormal = bitangent1;
        data[2].tangent = tangent1;

        data[3].binormal = bitangent2;
        data[3].tangent = tangent2;

        QSharedPointer<VertexArray> va = VertexArray::create();
        va->bind();
        QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
        buffer->setData(6 * sizeof(PlaneVertex), data);
        LayoutBuffer layout;
        layout.push<QVector3D>("POSITION");
        layout.push<QVector3D>("NORMAL");
        layout.push<QVector2D>("TEXCOORD");
        layout.push<QVector3D>("BINORMAL");
        layout.push<QVector3D>("TANGENT");
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

    QSharedPointer<CGFF::Mesh> CreateScreenQuad(QSharedPointer<CGFF::MaterialInstance> material)
    {
        struct QuadVertex
        {
            QVector3D position;
            QVector2D uv;
        };

        QuadVertex data[4];

        data[0].position = QVector3D(-1.0, 1.0, 0.0f);
        data[0].uv = QVector2D(0.0f, 1.0f);

        data[1].position = QVector3D(-1.0f, -1.0f, 0.0f);
        data[1].uv = QVector2D(0.0f, 0.0f);

        data[2].position = QVector3D(1.0f, 1.0f, 0.0f);
        data[2].uv = QVector2D(1.0f, 1.0f);

        data[3].position = QVector3D(1.0f, -1.0f, 0.0f);
        data[3].uv = QVector2D(1.0f, 0.0f);

        QSharedPointer<VertexArray> va = VertexArray::create();
        va->bind();
        QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
        buffer->setData(sizeof(QuadVertex) * 4, data);
        LayoutBuffer layout;
        layout.push<QVector3D>("POSITION");
        layout.push<QVector2D>("TEXCOORD");
        buffer->setLayout(layout);

        va->pushBuffer(buffer);
        uint indices[6] = { 0, 1, 2, 2, 3, 1, };
        QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 6);

        va->unBind();
        return QSharedPointer<Mesh>(new Mesh(va, ib, material));
    }
}
