#include "model.h"
#include <QFile>
namespace CGFF {

    Model::Model(const QString& path, QSharedPointer<MaterialInstance> materialInstance)
        : m_mesh(nullptr)
    {
        if (load(path))
            m_mesh->SetMaterial(materialInstance);
        else
            qFatal("Can't load model from ", path);
    }

    Model::~Model()
    {
    }

    bool Model::load(const QString& path)
    {
        //QFile file(path);
        //if (!file.exists())
        //    return false;

        //VertexSet inputVertices;
        //QVector<Vertex> vertices;
        //QVector<uint> indices;
        //QHash<IndexSet, int> mapping;

        //if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        //    return false;

        //while (!file.atEnd())
        //{
        //    QByteArray line = file.readLine();
        //    const char* cstr = line.constData();
        //    if (strstr(cstr, "#")) // Comment
        //    {
        //        continue;
        //    }
        //    else if (strstr(cstr, "v"))
        //    {
        //        if (strstr(cstr, "vt"))
        //        {
        //            QVector2D uv;
        //            float x, y;
        //            int result = sscanf(cstr, "%*s %f %f", &x, &y);
        //            if (result == 0)
        //                continue;

        //            uv.setX(x);
        //            uv.setY(y);
        //            inputVertices.uvs.push_back(uv);
        //        }
        //        else if (strstr(cstr, "vn"))
        //        {
        //            QVector3D normal;
        //            float x, y, z;
        //            int result = sscanf(cstr, "%*s %f %f %f", &x, &y, &z);
        //            if (result == 0)
        //                continue;

        //            normal.setX(x);
        //            normal.setY(y);
        //            normal.setZ(z);

        //            inputVertices.normals.push_back(normal);
        //        }
        //        else
        //        {
        //            QVector3D position;
        //            float x, y, z;
        //            int result = sscanf(cstr, "%*s %f %f %f", &x, &y, &z);
        //            if (result == 0)
        //                continue;

        //            position.setX(x);
        //            position.setY(y);
        //            position.setZ(z);

        //            inputVertices.positions.push_back(position);
        //        }
        //    }
        //    else if (strstr(cstr, "f"))
        //    {
        //        IndexSet indexSet[3];
        //        int result = sscanf(cstr, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &indexSet[0].position, &indexSet[0].uv, &indexSet[0].normal, &indexSet[1].position, &indexSet[1].uv, &indexSet[1].normal, &indexSet[2].position, &indexSet[2].uv, &indexSet[2].normal);
        //        if (result == 0)
        //            continue;

        //        insertVertex(vertices, indices, mapping, inputVertices, indexSet[0]);
        //        insertVertex(vertices, indices, mapping, inputVertices, indexSet[1]);
        //        insertVertex(vertices, indices, mapping, inputVertices, indexSet[2]);
        //    }
        //}

        //if (vertices.empty())
        //    return false;

        //m_shader->bind();
        //vao.create();
        //vao.bind();

        //vboBuf.create();
        //vboBuf.bind();
        //vboBuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        //vboBuf.allocate(&vertices[0], vertices.size() * sizeof(Vertex));

        //int position = m_shader->attributeLocation("position");
        //int normal = m_shader->attributeLocation("normal");
        //int uv = m_shader->attributeLocation("uv");

        //m_shader->enableAttributeArray(position);
        //m_shader->enableAttributeArray(normal);
        //m_shader->enableAttributeArray(uv);

        //m_shader->setAttributeBuffer(position, GL_FLOAT, 0, 3, sizeof(Vertex));
        //m_shader->setAttributeBuffer(normal, GL_FLOAT, offsetof(Vertex, normal), 3, sizeof(Vertex));
        //m_shader->setAttributeBuffer(uv, GL_FLOAT, offsetof(Vertex, uv), 2, sizeof(Vertex));

        //indexBuf = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        //indexBuf.create();
        //indexBuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        //indexBuf.bind();
        //indexBuf.allocate(&indices[0], indices.size()* sizeof(uint));
        //indexBuf.release();

        //vao.release();
        //m_shader->release();

        //m_mesh = QSharedPointer<Mesh>(new Mesh(&vao, &indexBuf, nullptr));

        return true;
    }

    //void Model::insertVertex(QVector<Vertex>& vertices, QVector<uint>& indices, QHash<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet)
    //{
    //    auto lookup = mapping.find(indexSet);
    //    if (lookup != mapping.end())
    //    {
    //        indices.push_back(lookup.value());
    //    }
    //    else
    //    {
    //        mapping[indexSet] = (int)vertices.size();
    //        indices.push_back(vertices.size());
    //        Vertex vertex = { inputVertices.positions[indexSet.position - 1], inputVertices.normals[indexSet.normal - 1], inputVertices.uvs[indexSet.uv - 1] };
    //        vertices.push_back(vertex);
    //    }
    //}

    void Model::render(Renderer3D& renderer)
    {
        m_mesh->render(renderer);
    }
}